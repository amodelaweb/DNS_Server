#include <iostream>
#include <fstream>
#include "readMasterFile.h"
#include "DNS_Query.h"
#include "DNS_Server.h"
using namespace std;

int main ()
{

  std::cout<<"\n Lol \n";
  DNS::MasterFile master= DNS::MasterFile();
  std::map<std::string, std::string> a= master.ReadFile("masterfile.txt");
  std::map<std::string, std::string>::iterator it = a.begin();

  for(;it!=a.end();it++){
    std::cout<<"*"<<it->first<<"*"<<"   "<<"-"<<it->second<<"-"<<std::endl;
  }
  return 0;
}
