#ifndef __DNS_Resolver_HXX
#define __DNS_Resolver_HXX

#include "DNS_Resolver.h"

void DNS::DNS_Resolver::init(const std::string& filename){
  MasterFile file= MasterFile();
  this->masterFile= file.leerArchivo(filename);
}

std::string DNS::DNS_Resolver::find(std::string domain, std::string type){
  bool x=true;
  for(int i=0;i<4;i++){
    if(i==3){
      if(domain[i]!='.'){
        x=false;
      }
    }
    else{
      if(domain[i]!='w'){
        x=false;
      }
    }
  }
  if(x){
    domain= "www."+domain;
  }
  std::multimap<std::string, std::string>::iterator it=this->masterFile.find(domain);
  std::pair<std::multimap<std::string,std::string>::iterator,std::multimap<std::string,std::string>::iterator> ret;
  ret= this->masterFile.equal_range(it->first);
  for(std::multimap<std::string,std::string>::iterator it2=ret.first;it2!=ret.second;++it2){
    if(it2->second.size()>16&&type=="AAAA"){
      return it2->second;
    }
    if(it2->second.size()<16&&type=="A"){
      return it2->second;
    }
  }
  return "error";
}

void DNS::DNS_Resolver::process(DNS_Query& query) throw (){
  std::string qName = query.getQName();
  std::string ipAddress = "";//convert(qName);
  /*std::string domainName = this->masterFile.find(ipAddress)->second;

  query.putQdCount(1);
  query.putAnCount(1);
  query.putRData(domainName);

  std::cout << std::endl << "Query for: " << ipAddress;
  std::cout << std::endl << "query with: ";

  if (domainName.empty()) {
      std::cout << "NameError" << std::endl;
      query.headerRCode(DNS_Query::Code::NameError);
      query.putRdLength(1); // null label
  }
  else {
      std::cout << domainName << std::endl;
      query.headerRCode(DNS_Query::Code::Ok);
      query.putRdLength(domainName.size()+2); // + initial label length & null label
  }
      query.setRCode(DNS_Query::Code::Ok);
      query.setRdLength(domainName.size()+2); // + initial label length & null label
  }*/
}

#endif
