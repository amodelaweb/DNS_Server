#include "DNS_Server.h"
#include <exception>

int main(int argc, char const *argv[]) {
  DNS::Server s;
  std::string file_name = "masterfile.txt" ;
  try {

    s.init(1025 , file_name);
    s.run();
  } catch (DNS::DNSException  & ex) {
    std::cout << ex.what();
  }

  return 0;
}
