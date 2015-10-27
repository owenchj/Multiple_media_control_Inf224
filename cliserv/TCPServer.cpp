//
//  TCPServer.cpp: TCP/IP INET Server.
//  (c) Eric Lecolinet - Telecom ParisTech - 2015.
//  http://www.telecom-paristech.fr/~elc
//

#include <unistd.h>
#include <iostream>
#include "TCPServer.h"
using namespace std;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TCPServer::Cnx::Cnx(TCPServer* server, Socket* socket)
: SocketBuffer(socket), _server(server), _thread(0) {
                          // pthread_create() cree un thread qui appelle start()
  pthread_create(&_thread, NULL, start, this);
}

void* TCPServer::Cnx::start(void* cnxptr) {        // called by pthread_create()
  Cnx* cnx = static_cast<Cnx*>(cnxptr);
  cnx->_server->readMessages(cnx);
  
  // liberer les ressources
  delete cnx->_sock;                             // detruit donc ferme le socket
  pthread_t thread = cnx->_thread;
  delete cnx;
  if (thread != 0) pthread_exit(NULL);    // ATTENTION: doit etre en dernier !!!
  return nullptr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TCPServer::Lock::Lock(TCPServer::Cnx& cnx, bool writeMode) : _cnx(cnx) {
  if (writeMode)
    pthread_rwlock_wrlock(&(_cnx._server->_threadlock)); // blocks in WRITE mode
  else
    pthread_rwlock_rdlock(&(_cnx._server->_threadlock)); // blocks in READ mode
}

TCPServer::Lock::~Lock() {
  pthread_rwlock_unlock(&(_cnx._server->_threadlock));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TCPServer::TCPServer() : _servsock() {
  pthread_rwlock_init(&_threadlock, NULL);
}

TCPServer::~TCPServer() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int TCPServer::run(int port)
{
  int status = _servsock.bind(port);  // lier le ServerSocket a ce port
  
  if (status < 0) {
    printMsg("Can't bind on port: " + to_string(port));
    return status;   // returns negative value, see Socket::bind()
  }
  
  while (true) {
    Socket* socket = _servsock.accept();
    if (!socket) {
      printMsg("accept() failed");
      continue;     // cas d'erreur : va a la prochaine iteration de while()
    }

    // lance la lecture des messages de ce socket dans un thread
    Cnx* c = new Cnx(this, socket);
    if (c->_thread == 0) {
      printMsg("pthread_create() failed");
      delete c;
    }
  }
  
  return 0;  // means OK
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::readMessages(Cnx* cnx) {
  while (true) {
    string request, response;
    
    // lire les données envoyées par le client
    // SocketBuffer::readLine() lit jusqu'au premier délimiteur (qui est supprimé)
    ssize_t received = cnx->readLine(request);

    if (received < 0) {
      printMsg("Read error", cnx);
      return;
    }
    
    if (received == 0) {
      printMsg("Connection closed by client", cnx);
      return;
    }
    
    // traiter le message et retourner la reponse
    // ferme la connection si la valeur de retour est false
    if (_callback && !_callback->callFunc(*cnx, request, response)) {
      printMsg("Closing connection with client", cnx);
      return;
    } 
    
    // toujours envoyer une reponse au client sinon il va se bloquer !
    // SocketBuffer::writeLine() envoie tout et rajoute le delimiteur
    ssize_t sent = cnx->writeLine(response);
    
    if (sent < 0) {
      printMsg("Write error", cnx);
      return;
    }
    
    if (sent == 0) {
      printMsg("Connection closed by client", cnx);
      return;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::printMsg(const string& msg, const TCPServer::Cnx* cnx) {
  if (cnx)
    cerr << "TCPServer: " << msg << " (connection: " << cnx << ")" << endl;
  else
    cerr << "TCPServer: " << msg << endl;
}
