//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2015.
//

#include <iostream>
#include <string>
#include "TCPServer.h"
using namespace std;

const int DEFAULT_PORT = 3331;

class MyApp {
public:
  
  /// Cette fonction est appelée chaque fois qu'il y a une requête à traiter.
  /// - 'request' contient la requête
  /// - 'response' sert à indiquer la réponse qui sera renvoyée au client
  /// - si la fonction renvoie false la connexion est close.
  //
  // Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
  // un thread par client).
  // Si le verrou 'lock' est bloqué en mode WRITE, les autres appels sont bloqués
  // jusqu'à la fin l'appel qui a bloqué le verrou.
  //
  bool processRequest(TCPServer::Cnx& cnx, const string& request, string& response)
  {
    // mettre cette variable à true si la commande modifie les donnees du programme
    bool changeData = false;
    if (request == "delMedias" || request == "delGroups") changeData = true;
    
    // suivant le cas on bloque le verrou en mode WRITE ou en mode READ
    TCPServer::Lock lock(cnx, changeData);
    
    cerr << "request: '" << request << "'" << endl;
    
    // simule un traitement long (décommenter pour tester le verrou)
    // if (changeData) sleep(10); else sleep(5);
    
    response = "OK: " + request;
    cerr << "response: '" << response << "'" << endl;
    
    // renvoyer false pour clore la connexion avec le client
    return true;
  }
};


int main(int argc, char* argv[])
{
  TCPServer * server = new TCPServer();
  MyApp * app = new MyApp();
  server->setCallback(app, &MyApp::processRequest);
  
  int port = (argc >= 2) ? atoi(argv[1]) : DEFAULT_PORT;
  cout << "Starting Server on port " << port << endl;
  int status = server->run(port);
  
  if (status < 0) {
    cerr << "Could not start Server on port " << port << endl;
    return 1;
  }
  else return 0;
}

