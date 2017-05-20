#ifndef __DNS_Resolver_HXX
#define __DNS_Resolver_HXX

#include "DNS_Resolver.h"

void DNS::DNS_Resolver::init(const std::string& filename){
  MasterFile file= MasterFile();
  this->masterFile= file.leerArchivo(filename);
}

void DNS::DNS_Resolver::process(DNS_Query& query) throw (){
  std::string qName = query.getQName();
  std::string ipAddress = "";//convert(qName);
  std::string domainName = this->masterFile.find(ipAddress)->second;

  query.setQdCount(1);
  query.setAnCount(1);
  query.setRdata(domainName);

  std::cout << std::endl << "Query for: " << ipAddress;
  std::cout << std::endl << "query with: ";

  if (domainName.empty()) {
      std::cout << "NameError" << std::endl;
      query.setRCode(DNS_Query::Code::NameError);
      query.setRdLength(1); // null label
  }
  else {
      std::cout << domainName << std::endl;
      query.setRCode(DNS_Query::Code::Ok);
      query.setRdLength(domainName.size()+2); // + initial label length & null label
  }
}

#endif
