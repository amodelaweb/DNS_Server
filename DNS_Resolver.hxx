#ifndef __DNS_Resolver_HXX
#define __DNS_Resolver_HXX

#include "DNS_Resolver.h"

/*=============================================================================================================================*/
void DNS::DNS_Resolver::init(const std::string& filename){
  MasterFile file= MasterFile();
  this->Records= file.ReadFile(filename);
}
/*=============================================================================================================================*/
std::string DNS::DNS_Resolver::find(std::string domain, unsigned int type){
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
  std::multimap<std::string, std::string>::iterator it=this->Records.find(domain);
  std::pair<std::multimap<std::string,std::string>::iterator,std::multimap<std::string,std::string>::iterator> ret;
  ret= this->Records.equal_range(it->first);
  bool yes = false ;
  int type1 = -1 ;
  std::string buffaux ;
  for(std::multimap<std::string,std::string>::iterator it2=ret.first;it2!=ret.second && !yes;++it2){
    if(it2->second.size()>16&&type==14){
      type1 = 0 ;
      buffaux = it2->second ;
      yes = true ;
    }
    if(it2->second.size()<16&&type==1){
      type1 = 1 ;
      yes = true ;
      buffaux = it2->second ;
    }
  }
  if(type1 == 0 ){
    return buffaux ;
  }else if(type1 == 1){
    return buffaux ;
  }
  return "error";
}
/*=============================================================================================================================*/
void DNS::DNS_Resolver::process(DNS_Query& query) throw (){
  std::string qName = query.obtainQName();
  std::string ipAddress = "";
  std::string domainName = "";
  unsigned int type = query.obtainQType();

  switch (type) {
    case 1:
    ipAddress = this->find(qName , 1);
    break;
    case 12:
    std::string ipName = this->ReverseIP(qName);
    domainName = this->findIP(ipName);
    break ;

  }

  query.putAll();
  query.putQdCount(1);
  query.putAnCount(1);
  if(type == 1){
    query.putRData(ipAddress);
  }else if(type == 12){
    query.putRData(domainName);
  }
  if(ipAddress == "error" || domainName == "error"){
    std::cout<<"\n Name error !! "<<std::endl;
    query.putRCode(DNS_Query::NameError);
    query.putRdLength(1);
  }
  else{
    if(type == 1){
      std::cout<<"\n Ip Adress : "<<ipAddress;
      query.putRdLength(ipAddress.size() + 2) ;
    }else if(type == 12){
      std::cout<<"\n Domain Name : "<<domainName;
      query.putRdLength(domainName.size() + 2);
    }
    query.putRCode(DNS_Query::Ok);

  }

}
/*=============================================================================================================================*/
std::string DNS::DNS_Resolver::ReverseIP(const std::string& ip) throw() {

  int pos_n = ip.find(".in-addr.arpa");
  if (pos_n == std::string::npos){
    return std::string();
  }

  std::string tmp(ip, 0, pos_n);
  std::string ipAddress;
  while ((pos_n = tmp.rfind('.')) != std::string::npos) {

    ipAddress.append(tmp, pos_n+1, tmp.size());
    ipAddress.append(".");
    tmp.erase(pos_n, tmp.size());
  }
  ipAddress.append(tmp, 0, tmp.size());

  return ipAddress;
}
/*=============================================================================================================================*/
std::string DNS::DNS_Resolver::findIP(std::string ipName){
  std::multimap<std::string , std::string > temp ;
  std::multimap<std::string , std::string >::iterator it ;
  std::string stemp ;
  for(it = this->Records.begin() ; it != this->Records.end() ; it++){
    temp.insert(std::pair<std::string , std::string> (it->second , it->first)) ;
  }
  it = temp.find(ipName);
  if (it != this->Records.end()){
    return it->second ;
  }else{
    return "error";
  }
}
/*=============================================================================================================================*/
#endif
