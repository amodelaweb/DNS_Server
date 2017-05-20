#ifndef _DNS_SERVER_H
#define	_DNS_SERVER_H

#include <netinet/in.h>

namespace DNS{
  class Server{
  public:
    Server();
    ~ Server() = default ;
    void init(int port) throw (Exception);
    void run() throw();
  private:
    static const int BUFFER_SIZE = 1024;
    struct sockaddr_in m_address;
    int m_sockfd;
    DNS_Resolver* resolver ;
  };
}
#include "DNS_Server.hxx"

#endif
