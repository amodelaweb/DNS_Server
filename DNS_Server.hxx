#ifndef _DNS_SERVER_HXX
#define	_DNS_SERVER_HXX
#include "DNS_Server.h"
#include "DNS_Resolver.h"

const std::string red1("\x1B[31m");
const std::string blue1("\x1B[34m") ;
const std::string green1("\033[1;32m");
const std::string yellow1("\033[1;33m");
const std::string cyan1("\033[0;36m");
const std::string magenta1("\033[0;35m");
const std::string reset1("\033[0m");
const std::string bold1("\x1B[1m") ;
const std::string white1("\x1B[37m");
const std::string underline1("\x1B[4m");
const std::string backgroundblue1("\x1B[44m");
const std::string backgroundblack1("\x1B[49m");
const std::string backgroundwhite1("\x1B[47m");

/*=============================================================================================================================*/
DNS::Server::Server(){

}
/*=============================================================================================================================*/
void DNS::Server::init(int port , std::string& filename) throw (DNSException) {

  if (this->resolver.init(filename) ){
    this->s_sockfd = socket (AF_INET,SOCK_DGRAM,0);
    if(s_sockfd == -1){
      std::cout<<bold1<<red1 ;
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
      std::cout<<bold1<<red1 ;
      std::string error1 ("Could not bind the port: ");
      error1 += std::strerror(errno);
      error1 += "\n";
      DNSException e(error1);
      throw (e);
    }

    std::cout <<bold1<<yellow1<< "\nListening in port: "<<port<<"."<<std::endl;
  }else{
    std::cout<<bold1<<red1 ;
    std::string error1 ("Could not open the file ! ");
    DNSException e(error1);
    throw (e);
  }
}
/*=============================================================================================================================*/
void DNS::Server::run() throw(){

  std::cout <<magenta1<<bold1<< "\n Server is waiting for connections....." <<std::endl;
  struct sockaddr_in clientAddress;
  socklen_t addr_len = sizeof (struct sockaddr_in);
  struct sockaddr_storage addr;
  char ipstr[INET_ADDRSTRLEN];
  char buffer[BUFFER_SIZE];

  while(true){
    int number_bytes =   0;
    number_bytes = recvfrom(this->s_sockfd , buffer , BUFFER_SIZE , 0 , (struct sockaddr*) &clientAddress , &addr_len);
    s_query = new DNS_Query();
    s_query->decodeQ(buffer , number_bytes);
    std::cout<<bold1<<underline1<<cyan1 ;
    printf("\n Recieved %d bytes of data in buffer\n", number_bytes);
    std::cout<<bold1<<green1 ;
    printf("\nFrom IP address %s",  inet_ntop(AF_INET, (void*)&clientAddress.sin_addr ,ipstr, sizeof ipstr));
    std::cout<<bold1<<yellow1 ;
    std::cout<<"\n Recieved Data : -"<<s_query->obtainQName()<<"-";
    std::cout<<bold1<<white1 ;

    this->resolver.process(*s_query);
    memset(buffer, 0, BUFFER_SIZE);

    number_bytes = s_query->resposeCode(buffer);
    sendto(this->s_sockfd, buffer, number_bytes, 0, (struct sockaddr *) &clientAddress,
           addr_len);
       memset(buffer, 0, BUFFER_SIZE);
       delete s_query ;
  }
}
/*=============================================================================================================================*/
#endif
