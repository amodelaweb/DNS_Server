#ifndef _DNS_SERVER_H
#define	_DNS_SERVER_H

#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>
#include "DNS_Query.h"
#include "DNS_Resolver.h"

#define BUFFER_SIZE 1024
/*=============================================================================================================================*/
namespace DNS{
/*=============================================================================================================================*/
  struct DNSException{
    std::string data ;
    DNSException(std::string& data) : data(data){}
    const char* what() const throw() {
      return data.data();
    }
  };
/*=============================================================================================================================*/
  class Server{
  public:
    Server();
    ~ Server() = default ;
    void init(int port  , std::string& filename) throw (DNSException);
    void run() throw();
  private:

    struct sockaddr_in s_address;
    int s_sockfd;
    DNS_Query s_query;
    DNS_Resolver resolver ;
  };
}
#include "DNS_Server.hxx"

#endif
