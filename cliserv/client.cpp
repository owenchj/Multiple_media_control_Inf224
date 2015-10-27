//
// Client C++ pour communiquer avec un serveur TCP
// eric lecolinet - telecom paristech - 2015
//

#include <iostream>
#include "Socket.h"
using namespace std;

static const string DEFAULT_HOST = "localhost";
static const int DEFAULT_PORT = 3331;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class Client {
public:
  Client(const string& host, int port);
  int getStatus() const {return status;}
  int send(const string& request, string& response);
private:
  Socket sock;
  SocketBuffer sockbuf;
  int status;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

///
/// Lit une requete depuis le Terminal, envoie cette requete au serveur,
/// recupere sa reponse et l'affiche sur le Terminal.
/// Noter que le programme bloque si le serveur ne repond pas.
///
int main(int argc, char* argv[]) {
  string host = (argc >=2) ? argv[1] : DEFAULT_HOST;
  int port = (argc >=3) ? atoi(argv[2]) : DEFAULT_PORT;
  
  Client client(host, port);
  
  if (client.getStatus() < 0) {
    cerr << "Client: Couldn't connect to: "<< host<<":"<<port << endl;
    return 1;
  }
  
  cout << "Client connected to "<< host<<":"<<port << endl;
  
  while (cin.good()) {
    cout << "Request: ";
    string request, response;
    
    getline(cin, request);
    if (request == "quit") return 0;
    
    if (client.send(request, response) >= 0)
      cout << "Response: '" << response << "'" << endl;
    else {
      cerr << "Client: IO error "<< endl;
      return 2;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

///
/// Initialise la connexion.
/// Renvoie une valeur negative en cas d'erreur.
///
Client::Client(const string& host, int port) : sockbuf(sock), status(0) {
  status = sock.connect(host, port);
  if (status < 0) {
    switch (status) {
      case Socket::Failed:
        cerr << "Client: Couldn't reach host "<<host<<":"<<port << endl;
        return;
      case Socket::UnknownHost:
        cerr << "Client: Couldn't find host "<<host<<":"<<port << endl;
        return;
      default:
        cerr << "Client: Couldn't connect host "<<host<<":"<<port << endl;
        return;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

///
/// Envoie une requete au server et retourne sa reponse.
/// Renvoie une valeur negative en cas d'erreur.
/// Noter que la methode bloque si le serveur ne repond pas.
///
int Client::send(const string& request, string& response) {
  // Envoyer la requete au serveur
  if (sockbuf.writeLine(request) < 0) {
    cerr << "Client: Could not send message" << endl;
    return -1;
  }
  
  // Recuperer le resultat envoye par le serveur
  if (sockbuf.readLine(response) < 0) {
    cerr << "Client: Could not receive message" << endl;
    return -2;
  }
  
  return 0;
}
