#ifndef _DNS_SERVER_HXX
#define	_DNS_SERVER_HXX
#include "DNS_Server.h"

/*=============================================================================================================================*/
DNS::Server::Server(){

}
/*=============================================================================================================================*/
void DNS::Server::init(int port) throw (DNSException) {

  this->s_sockfd = socket (AF_INET,SOCK_DGRAM,0);
  if(s_sockfd == -1){
    std::string error1 ("Could not open socket : ");
    error1 += std::strerror(errno);
    DNSException e(error1);
    error1 += "\n";
    throw (e);
  }

  this->s_address.sin_family = AF_INET ;
  this->s_address.sin_addr.s_addr = INADDR_ANY ;
  this->s_address.sin_port = htons(port);

  int sbind = bind(this->s_sockfd , (struct sockaddr*)&this->s_address , sizeof(struct sockaddr_in));
  if(sbind != 0){
    std::string error1 ("Could not bind the port: ");
    error1 += std::strerror(errno);
    error1 += "\n";
    DNSException e(error1);
    throw (e);
  }
  sa.sa_handler = sigchld_handler; // reap all dead processes
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART;
if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
}

  std::cout << "\nListening in port: "<<port<<"."<<std::endl;
}
/*=============================================================================================================================*/
void DNS::Server::run() throw(){
  std::cout << "Server is waiting for connections....." <<std:: endl;
  struct sockaddr_in clientAddress;
  socklen_t addr_len = sizeof (struct sockaddr_in);
  char buffer[BUFFER_SIZE];
  while(true){
    int number_bytes =   0;
    number_bytes = recvfrom(this->s_sockfd , buffer , BUFFER_SIZE , 0 , (struct sockaddr*) &clientAddress , &addr_len);

    sendto(s_sockfd, buffer, number_bytes, 0, (struct sockaddr *) &clientAddress,
           addr_len);
  }
}
#endif
