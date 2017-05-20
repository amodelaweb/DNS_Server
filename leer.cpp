#include <iostream>
#include <fstream>
#include "readMasterFile.h"
using namespace std;

int main ()
{
  MasterFile master= MasterFile();
  std::map<std::string, std::string> a= master.leerArchivo("masterfile.txt");
  std::map<std::string, std::string>::iterator it = a.begin();
  for(;it!=a.end();it++){
    std::cout<<it->first<<"   "<<it->second<<std::endl;
  }
  return 0;
}
