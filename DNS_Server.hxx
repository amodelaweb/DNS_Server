#ifndef _DNS_SERVER_HXX
#define	_DNS_SERVER_HXX
#include "DNS_Server.h"
#include "DNS_Resolver.h"
/*=============================================================================================================================*/
DNS::Server::Server(){

}
/*=============================================================================================================================*/
void DNS::Server::init(int port , std::string& filename) throw (DNSException) {

  if (this->resolver.init(filename) ){
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

    std::cout << "\nListening in port: "<<port<<"."<<std::endl;
  }else{
    std::string error1 ("Could not open the file ! ");
    DNSException e(error1);
    throw (e);
  }
}
/*=============================================================================================================================*/
void DNS::Server::run() throw(){
  std::cout << "Server is waiting for connections....." <<std::endl;
  struct sockaddr_in clientAddress;
  socklen_t addr_len = sizeof (struct sockaddr_in);
  struct sockaddr_storage addr;
  char ipstr[INET_ADDRSTRLEN];
  char buffer[BUFFER_SIZE];

  printf("\nyo soy IP address %s\n",  inet_ntop(AF_INET, (void*)&this->s_address.sin_family ,ipstr, sizeof ipstr));
  while(true){
    int number_bytes =   0;
    number_bytes = recvfrom(this->s_sockfd , buffer , BUFFER_SIZE , 0 , (struct sockaddr*) &clientAddress , &addr_len);

    s_query.decodeQ(buffer , number_bytes);

    printf("\nRecibidos %d bytes of data in buffer\n", number_bytes);
    printf("\nFrom IP address %s",  inet_ntop(AF_INET, (void*)&clientAddress.sin_addr ,ipstr, sizeof ipstr));
    std::cout<<"\n Datos recibidos : -"<<s_query.obtainQName()<<"-";

  
    this->resolver.process(s_query);
    memset(buffer, 0, BUFFER_SIZE);
    number_bytes = s_query.resposeCode(buffer);

    sendto(this->s_sockfd, buffer, number_bytes, 0, (struct sockaddr *) &clientAddress,
           addr_len);

  }
}
/*=============================================================================================================================*/
#endif
