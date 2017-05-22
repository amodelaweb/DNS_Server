#include "DNS_Server.h"
#include <exception>

int main(int argc, char const *argv[]) {

  if(argc != 3){
    std::cerr << "Usage: [Port] [M_Filename] \n" ;
    return 1 ;
  }
  unsigned int port = atoi(argv[1]);
  std::string file_name  = argv[2];

  DNS::Server s;
  try {
    s.init(port , file_name);
    s.run();
  } catch (DNS::DNSException  & ex) {
    std::cout << ex.what();
  }

  return 0;
}
