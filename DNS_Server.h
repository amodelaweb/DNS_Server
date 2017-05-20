#ifndef _DNS_SERVER_H
#define	_DNS_SERVER_H

#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <errno.h>

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
    void init(int port) throw (DNSException);
    void run() throw();
  private:
    static const int BUFFER_SIZE = 1024;
    struct sockaddr_in s_address;
    int s_sockfd;

  };
}
#include "DNS_Server.hxx"

#endif
