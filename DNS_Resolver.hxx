#ifndef __DNS_Resolver_HXX
#define __DNS_Resolver_HXX

#include "DNS_Resolver.h"

void DNS::DNS_Resolver::init(const std::string& filename){
  MasterFile file= MasterFile();
  this->masterFile= file.leerArchivo(filename);
}

#endif
