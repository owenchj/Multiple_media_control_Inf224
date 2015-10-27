//
//  Socket.h: Classes for TCP/IP and UDP Datagram INET Sockets.
//  (c) Eric Lecolinet - Telecom ParisTech - 2015.
//  http://www.telecom-paristech.fr/~elc
//
//  Classes:
//  - Socket: TCP/IP or UDP/Datagram Socket (AF_INET connections following IPv4)
//  - ServerSocket: TCP/IP Socket Server
//  - SocketBuffer: preserves record boundaries when exchanging data blocks or
//    text lines between TCP/IP sockets.
//

#ifndef __Socket__
#define __Socket__
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

#define IGNORE_SIGPIPE 1

#if defined(IGNORE_SIGPIPE) && defined(MSG_NOSIGNAL)
#  define _NO_SIGPIPE(flags) (flags | MSG_NOSIGNAL)
#else
#  define _NO_SIGPIPE(flags) (flags)
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** @brief TCP/IP or UDP/Datagram Socket.
 * This class encapsulates a TCP/IP or UDP/Datagram socket. AF_INET connections 
 * following the IPv4 Internet protocol are supported.
 *
 * ServerSocket should be used on the server side when using TCP/IP (@see ServerSocket).
 *
 * TCP/IP sockets do not preserve record boundaries: messages can be split or merged
 * @see SocketBuffer for a solution.
 *
 * @note SIGPIPE signals are ignored when using Linux, BSD or MACOSX.
 */
class Socket {
public:
  /** @brief Socket errors.
   * - Socket::Failed (-1): connection error (could not connect, could not bind, etc.)
   * - Socket::InvalidSocket (-2): invalid socket or wrong socket type
   * - Socket::UnknownHost (-3): could not reach host
   */
  enum Errors {Failed = -1, InvalidSocket = -2, UnknownHost = -3};

  /** @brief Creates a new Socket.
   * Creates a AF_INET socket using the IPv4 Internet protocol. 
   * Type can be:
   * - SOCK_STREAM (the default) for TCP/IP connected stream sockets
   * - SOCK_DGRAM for UDP/datagram sockets
   */
  Socket(int type = SOCK_STREAM);
  
  /// Creates a Socket object from an existing socket file descriptor.
  Socket(int type, int sockfd);

  /// Destructor (closes the socket).
  virtual ~Socket();
  
  /** @brief Assigns the socket to the local address.
   * Typically used for UDP/Datagram sockets, @see Unix bind() system call for details.
   * @return 0 on success or a negative value on error which is one of Socket::Errors
   */
  virtual int bind(int port);
  
  /** @brief Assigns the socket to an address.
   * Typically used for UDP/Datagram sockets, @see Unix bind() system call for details.
   * @return 0 on success or a negative value on error which is one of Socket::Errors
   */
  virtual int bind(const std::string& host, int port);
  
  /** @brief Connects the socket to an address.
   * Typically used for TCP/IP sockets on the client side, @see Unix connect() system call
   * for details and ServerSocket for TCP/IP sockets on the server side.
   * @return 0 on success or a negative value on error which is one of Socket::Errors
   */
  virtual int connect(const std::string& host, int port);
  
  /** @brief Closes the socket.
   * @return 0 on success and -1 on error.
   */
  virtual int close();
  
  /// Returns true if the socket has been closed.
  bool isClosed() const {return _sockfd < 0;}
  
  /// Returns the Unix descriptor of the socket.
  int descriptor() {return _sockfd;}
    
  /** @brief Sends data to a connected socket.
   * Sends _len_ bytes to a TCP/IP socket.
   * @return the number of bytes which was sent except if:
   * - _len_ is 0 or shutdownInput() was called on the other side (0 is returned)
   * - an error occurred (-1 = Socket::Failed is returned)
   * @see Unix send() system call for details.
   * @note that TCP/IP sockets do not preserve record boundaries, @see SocketBuffer for a solution.
   */
  ssize_t send(const void* buf, size_t len, int flags = 0) {
    return ::send(_sockfd, buf, len, _NO_SIGPIPE(flags));
  }
  
  /** @brief Receives data from a connected socket.
   * Reads at most _len_ bytes from a TCP/IP socket. Normally, this function blocks 
   * the caller until data is present.
   * @return the number of bytes which was received except if:
   * - _len_ is 0 or shutdownOutput() was called on the other side (0 is returned)
   * - an error occurred (-1 = Socket::Failed is returned)
   * @see Unix recv() system call for details.
   * @note that TCP/IP sockets do not preserve record boundaries, @see SocketBuffer for a solution.
   */
  ssize_t receive(void* buf, size_t len, int flags = 0) {
    return ::recv(_sockfd, buf, len, flags);
  }
  
  /** @brief Sends data to a datagram socket.
   * Sends _len_ bytes to a datagram socket.
   * @return the number of bytes which was sent or -1 (Socket::Failed) if an error occurred.
   * @see Unix sendto() system call for details.
   */
  ssize_t sendTo(const void* buf, size_t len, int flags,
                 const struct sockaddr* dest_addr, socklen_t addrlen) {
    return ::sendto(_sockfd, buf, len, _NO_SIGPIPE(flags), dest_addr, addrlen);
  }

  /** @brief Receives data from datagram socket.
   * Reads at most _len_ bytes from a datagram socket, Normally, this function blocks 
   * the caller until data is present.
   * @return the number of bytes which was received or -1 (Socket::Failed) if an error occurred.
   * @see Unix recvfrom() for details.
   */
  ssize_t receiveFrom(void* buf, size_t len, int flags,
                      struct sockaddr* src_addr, socklen_t* addrlen) {
    return ::recvfrom(_sockfd, buf, len, flags, src_addr, addrlen);
  }

  /// Disables further receive operations.
  virtual void shutdownInput();
  
  /// Disables further send operations.
  virtual void shutdownOutput();
  
  /// Sets the size of the TCP/IP input buffer.
  int setReceiveBufferSize(int size);
    
  /// Enables/disables the SO_REUSEADDR socket option.
  int setReuseAddress(bool);
  
  /// Sets the size of the TCP/IP output buffer.
  int setSendBufferSize(int size);

  /// Enables/disables SO_LINGER with the specified linger time in seconds.
  int setSoLinger(bool, int linger);
  
  /// Enables/disables SO_TIMEOUT with the specified timeout (in milliseconds).
  int setSoTimeout(int timeout);
  
  /// Enables/disables TCP_NODELAY (turns on/off TCP coalescence).
  int setTcpNoDelay(bool);

  /// Gets the size of the TCP/IP input buffer.
  int getReceiveBufferSize() const;
  
  /// Gets SO_REUSEADDR state.
  bool getReuseAddress() const;
  
  /// Gets the size of the TCP/IP output buffer.
  int getSendBufferSize() const;
  
  /// Gets SO_LINGER state and the specified linger time in seconds.
  bool getSoLinger(int& linger) const;
  
  /// Gets SO_TIMEOUT value.
  int getSoTimeout() const;
  
  /// Gets TCP_NODELAY state.
  bool getTcpNoDelay() const;
  
  /// Initializes a local INET4 address, returns 0 on success, -1 otherwise.
  virtual int setLocalAddress(struct sockaddr_in& addr, int port);
  
  /// Initializes a remote INET4 address, returns 0 on success, -1 otherwise.
  virtual int setAddress(struct sockaddr_in& addr, const std::string& host, int port);

private:
  friend class ServerSocket;
  int _sockfd;
  Socket(const Socket&);              /// disables the copy constr.
  Socket& operator=(const Socket&);   /// disables the assignment operator.
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** @brief TCP/IP Socket Server.
 * This class encapsulates a TCP/IP socket server. AF_INET connections following
 * the IPv4 Internet protocol are supported.
 *
 * Class Socket should be used on the client side (@see Socket).
 *
 * TCP/IP sockets do not preserve record boundaries, @see SocketBuffer for a solution.
 */
class ServerSocket {
public:
  /** @brief Creates a new server socket.
   * Creates a listening socket that waits for connection requests by TCP/IP clients.
   */
  ServerSocket();
  
  virtual ~ServerSocket();
  
  /** @brief Accepts a new connection request and returns the corresponding socket.
   * By default, this function blocks the caller until a connection is present.
   * @return the new Socket or nullptr on error.
   */
  virtual Socket* accept();

  /** @brief Assigns the socket to the local address.
   * The socket must be bound before using it.
   * @return 0 on success or a negative value on error which is one of Socket::Errors
   */
  virtual int bind(int port, int backlog = 50);
  
  /// Closes the socket.
  virtual int close();

  /// Returns true if the socket has been closed.
  bool isClosed() const {return _sockfd < 0;}
  
  /// Returns the Unix descriptor of the socket.
  int descriptor() {return _sockfd;}
  
  /// Sets the SO_RCVBUF option to the specified value.
  int setReceiveBufferSize(int size);
  
  /// Enables/disables the SO_REUSEADDR socket option.
  int setReuseAddress(bool);
  
  /// Enables/disables SO_TIMEOUT with the specified timeout (in milliseconds).
  int	setSoTimeout(int timeout);
  
  /// Turns on/off TCP coalescence (useful in some cases to avoid delays).
  int setTcpNoDelay(bool);
  
private:
  int _sockfd;                                    ///< listening socket.
  ServerSocket(const ServerSocket&);             ///< disables the copy constr.
  ServerSocket& operator=(const ServerSocket&);  ///< disables the assignment operator.
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** @brief Class for exchanging text strings between TCP/IP sockets.
 * TCP/IP connected sockets do not preserve record boundaries. Messages can be split
 * or merged so that one call to Socket::send() on the sending side does not necessarily
 * correspond to one call to Socket::receive() on the receiving side.
 *
 * The methods of this class solve this problem:
 * - by calling Socket::send() or Socket::receive() as many times as needed
 * - by using a Line Separator to separate text lines (@see setSeparator())
 */
class SocketBuffer {
public:
  /** @brief constructor.
   * The argument must be a valid connected TCP/IP Socket (i.e. of SOCK_STREAM type)
   * that must NOT be destructed while this SocketBuffer is used.
   */
  SocketBuffer(Socket* socket, size_t inputBufferSize = 8192, size_t ouputBufferSize = 8192);
  SocketBuffer(Socket& socket, size_t inputBufferSize = 8192, size_t ouputBufferSize = 8192);
  
  virtual ~SocketBuffer();
  
  Socket* socket() {return _sock;}
  
  /** @brief changes the Line Separators.
   * the argument is a character or a negative value (see below):
   * - if _inputSeparator_ is < 0 (the default) a line is considered to be terminated
   *   by any one of '\n' or '\r' or '\n' followed by '\r'
   * - if _outputSeparator_ is < 0 a line is terminated by '\n' followed by '\r'.
   *   The default value is '\n'.
   */
  virtual void setSeparators(int inputSeparator, int outputSeparator);
  
  /** @brief returns the Line Separators.
   * @see setSeparators().
   */
  virtual void getSeparators(int& inputSeparator, int& outputSeparator) const;

  /** @brief Reads a line of text from a connected socket.
   * The text is stored in the string given as an argument.
   * The other side must send a line of text ended by a Line Separator (@see setSeparator())
   * which is automatically done by writeLine(). The separator is not stored in the argument.
   * @return the number of bytes that was received (including the separator) except if:
   * - shutdownOutput() was called on the other side (0 is returned)
   * - an error occured (Socket::Failed is returned)
   * - the socket is invalid (Socket::InvalidSocket is returned)
   * @note this method may block.
   */
  virtual ssize_t readLine(std::string& str);
  
  /** @brief Sends a line of text to a connected socket.
   * Sends the string given as an argument. 
   * A Line Separator is automatically added (@see setSeparator()).
   * @return the number of bytes that was sent (including the separator) except if:
   * - shutdownInput() was called on the other side (0 is returned)
   * - an error occured (Socket::Failed is returned)
   * - the socket is invalid (Socket::InvalidSocket is returned)
   * @note this method may block.
   */
  virtual ssize_t writeLine(const std::string& str);
  
  /* Receives a given number of characters from a connected socket.
   * Reads exactly _len_ bytes from the socket.
   * @return the number of characters received from the other side except if:
   * - shutdownOutput() was called on the other side (0 is returned)
   * - an error occured (Socket::Failed is returned)
   * - the socket is invalid (Socket::InvalidSocket is returned)
   * @note that this method may block.
   */
  virtual ssize_t read(char* buffer, size_t len);

  /* @brief Sends a given number of characters to a connected socket.
   * Writes _len_ bytes to the socket.
   * @return the number of characters sent to the other side except if:
   * - shutdownInput() was called on the other side (0 is returned)
   * - an error occured (Socket::Failed is returned)
   * - the socket is invalid (Socket::InvalidSocket is returned)
   * @note this method may block.
   */
  virtual ssize_t write(const char* str, size_t len);
  
private:
  SocketBuffer(const SocketBuffer&);             ///< disables the copy constr.
  SocketBuffer& operator=(const SocketBuffer&);  ///< disables the assignment operator.
  
protected:
  virtual bool retrieveLine(std::string& str, ssize_t received);
  size_t _inSize, _outSize;
  int _inSep, _outSep;
  Socket* _sock;
  struct InputBuffer* _in;
};


#endif
