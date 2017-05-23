#include "DNS_Server.h"
#include <exception>
#include <iostream>
#include <string.h>


const std::string red("\x1B[31m");
const std::string blue("\x1B[34m") ;
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");
const std::string bold("\x1B[1m") ;
const std::string white("\x1B[37m");
const std::string underline("\x1B[4m");
const std::string backgroundblue("\x1B[44m");
const std::string backgroundblack("\x1B[49m");
const std::string backgroundwhite("\x1B[47m");

int main(int argc, char const *argv[]) {
  std::cout<<bold<<green;
  std::cout<<backgroundblue;
  if(argc != 3){
    std::cerr << "Usage: "<<bold<<red<<"[Port]"<<bold<<cyan<<"[M_Filename] \n" ;
    std::cout<<reset;
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
