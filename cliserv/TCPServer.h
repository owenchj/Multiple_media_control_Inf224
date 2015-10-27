//
//  TCPServer.h: TCP/IP INET Server.
//  (c) Eric Lecolinet - Telecom ParisTech - 2015.
//  http://www.telecom-paristech.fr/~elc
//

#ifndef __TCPServer__
#define __TCPServer__
#include <memory>
#include <pthread.h>
#include "Socket.h"

/// @brief TCP/IP IPv4 server.
/// The server supports TCP/IP AF_INET connections (following the IPv4 Internet protocol)
/// with multiple clients. One thread is used per client.
///
/// The run() method binds an internal ServerSocket then starts an infinite main loop
/// that receives requests from clients. Requests can be received concurrently
/// thanks to threads.
///
/// A callback method is called each time the sever receives a request from a client
/// (@see setCallback() to set this method). This method can issue read and write locks
/// to avoid concurrency issues (@see Lock).
///
class TCPServer {
public:
  
  // - - - Connection - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  /// @brief represents a connection with a given client.
  class Cnx : public SocketBuffer {
  public:
    TCPServer* server() {return _server;}
    pthread_t  thread() {return _thread;}
  private:
    friend class TCPServer;
    Cnx(TCPServer*, Socket*);
    static void* start(void*);
    TCPServer* _server;
    pthread_t  _thread;
  };
  
  // - - - Lock - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  /// @brief locks the server in read mode or in write mode.
  /// In order to avoid concurrency problems between threads, the callback method
  /// that processes requests should instantiate a Lock object in the stack.
  /// The Lock must be instantiated in write mode if the request changes data,
  /// or in read mode otherwise.
  /// A write lock blocks all other locks (hence, all other threads) until the
  /// callback method that issued the write lock returns.
  ///
  class Lock {
  public:
    /// locks the connection in write mode if the second argument is true and in read mode otherwise.
    Lock(Cnx&, bool writeMode = false);
    ~Lock();
  private:
    Cnx& _cnx;
  };
  
  // - - - TCPServer API - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  /// @brief constructor: initializes the TCPServer.
  TCPServer();
  
  /// @brief destructor: cleans up the TCPServer.
  virtual ~TCPServer();
  
  /// @brief starts the main loop of the server on this port.
  /// This function binds an internal ServerSocket then starts an infinite main loop
  /// that receives requests from clients. The function creates one thread per client.
  /// @return 0 on normal termination or a negative value if the ServerSocket could not
  /// be bound (value is then one of Socket::Errors).
  ///
  virtual int run(int port);
  
  /// @brief changes the callback method that processes requests.
  /// The first argument must be an object, the second argument a method of this object.
  /// This method will be called each time the TCPServer receives a 'request' from a client
  /// in order to perform a computation and return a 'response' to this client.
  //  It should issue a read or a write Lock (@see Lock) before performing the
  //  computation to avoid concurrency problems.
  //
  /// Arguments and return value of the method:
  /// - the 'request' and the 'response' are provided through the corresponding
  ///   parameters of the method.
  /// - the connection with the client will be closed if the method returns false
  ///
  template <class T>
  void setCallback(T* obj, bool (T::*func)(Cnx&, const std::string& request, std::string& response)) {
    _callback.reset(new CallbackImpl<T>(obj, func));
  }
  
  // - - - Impl. - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

private:
  TCPServer(const TCPServer&);             ///< disables the copy constr.
  TCPServer& operator=(const TCPServer&);  ///< disables assignment.
  
protected:
  /// reads messages from a given client on the corresponding thread.
  virtual void readMessages(TCPServer::Cnx*);

  /// prints warning and error messages on the terminal.
  virtual void printMsg(const std::string& msg, const TCPServer::Cnx* = 0);

  // - - - Callback impl.
  class Callback {
  public:
    virtual bool callFunc(Cnx& cnx, const std::string& request, std::string& response) = 0;
  };
  
  template <class T> class CallbackImpl : public Callback {
    typedef bool (T::*Func)(Cnx&, const std::string&, std::string&);
    T* _obj;
    Func _func;
  public:
    CallbackImpl(T* obj, Func func) : _obj(obj), _func(func) {}
    
    virtual bool callFunc(Cnx& cnx, const std::string& request, std::string& response) {
      return (_obj->*_func)(cnx, request, response);
    }
  };
  
  // - - - instance variables.
  ServerSocket _servsock;
  std::shared_ptr<Callback> _callback;
  pthread_rwlock_t _threadlock;
};

#endif

