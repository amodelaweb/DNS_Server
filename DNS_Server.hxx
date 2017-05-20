#ifndef _DNS_SERVER_HXX
#define	_DNS_SERVER_HXX
#include "DNS_Server.h"

/*=============================================================================================================================*/
DNS::Server::Server(){

}
/*=============================================================================================================================*/
void DNS::Server::init(int port) throw (DNSException) {

  this->m_sockfd = socket (AF_INET,SOCK_DGRAM,0);
  this->m_address.sin_family = AF_INET ;
  this->m_address.sin_addr.s_addr = INADDR_ANY ;
  this->m_address.sin_port = htons(port);

  int sbind = bind(this->m_sockfd , (struct sockaddr*)&this->m_address , sizeof(struct sockaddr_in));
  if(sbind != 0){
    std::string error1 ("Could not bind the port: ");
    error1 += std::strerror(errno);
    DNSException e(error1);
    throw (e);
  }
  std::cout << "\nListening in port: "<<port<<"."<<std::endl;
}
/*=============================================================================================================================*/
void run() throw(){
  std::cout << "DNS Server is running..." <<std:: endl;
  struct sockaddr_in clientAddress;
  socklen_t addrLen = sizeof (struct sockaddr_in);
  char buffer[BUFFER_SIZE];
  while(true){
    int numberbytes = std::recvfrom(this->m_sockfd , buffer , BUFFER_SIZE , 0 , (struct sockaddr*) &clientAddress , &addrLen);
  }
}
#endif
