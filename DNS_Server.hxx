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
    throw (e);
  }
  this->s_address.sin_family = AF_INET ;
  this->s_address.sin_addr.s_addr = INADDR_ANY ;
  this->s_address.sin_port = htons(port);

  int sbind = bind(this->s_sockfd , (struct sockaddr*)&this->s_address , sizeof(struct sockaddr_in));
  if(sbind != 0){
    std::string error1 ("Could not bind the port: ");
    error1 += std::strerror(errno);
    DNSException e(error1);
    throw (e);
  }
  std::cout << "\nListening in port: "<<port<<"."<<std::endl;
}
/*=============================================================================================================================*/
void DNS::Server::run() throw(){
  std::cout << "DNS Server is running..." <<std:: endl;
  struct sockaddr_in clientAddress;
  socklen_t addrLen = sizeof (struct sockaddr_in);
  char buffer[BUFFER_SIZE];
  while(true){
    int numberbytes =   0;
    numberbytes = recvfrom(this->s_sockfd , buffer , BUFFER_SIZE , 0 , (struct sockaddr*) &clientAddress , &addrLen);

    sendto(s_sockfd, buffer, numberbytes, 0, (struct sockaddr *) &clientAddress,
           addrLen);
  }
}
#endif
