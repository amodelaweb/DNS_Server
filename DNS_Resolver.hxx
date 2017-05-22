#ifndef __DNS_Resolver_HXX
#define __DNS_Resolver_HXX

#include "DNS_Resolver.h"

/*=============================================================================================================================*/
bool DNS::DNS_Resolver::init( std::string& filename){
  MasterFile file=  MasterFile();
  if(file.ReadFile(filename)){
    this->Records = file.getRecords() ;
    return true ;
  }else{
    return false ;
  }
}
/*=============================================================================================================================*/
std::vector<std::string> DNS::DNS_Resolver::find(std::string domain, unsigned int type){

  std::vector<std::string> temp ;
  bool x=true;
  std::string temp1 = domain.substr(0,4);
  if(temp1 != "www."){
    domain= "www."+domain;
  }
  std::multimap<std::string, std::string>::iterator it=this->Records.find(domain);
  if(it != this->Records.end() ){
    std::pair<std::multimap<std::string,std::string>::iterator,std::multimap<std::string,std::string>::iterator> ret;
    ret= this->Records.equal_range(it->first);

    bool yes = false ;
    int type1 = -1 ;

    for(std::multimap<std::string,std::string>::iterator it2=ret.first;it2!=ret.second && !yes;++it2){
      if(it2->second.size()>16&&type==14){
        type1 = 0 ;
        temp.push_back(it2->second);
        yes = true ;
      }
      if(it2->second.size()<16&&type==1){
        type1 = 1 ;
        temp.push_back(it2->second);
      }
    }

    if(type1 == 0 ){
      return temp ;
    }else if(type1 == 1){
      return temp ;
    }
  }else{
    return temp;
  }
  return temp;
}
/*=============================================================================================================================*/
void DNS::DNS_Resolver::process(DNS_Query& query) throw (){
  std::string qName = query.obtainQName();
  std::vector<std::string> ipAddress ;
  std::vector<std::string> domainName ;
  unsigned int type = query.obtainQType();

  if(type == 1){

    ipAddress = this->find(qName , 1);
    if(ipAddress.empty() ) {
      ipAddress= redirect(qName);
    }
  }

  if(type == 12) {
    std::string ipName = this->ReverseIP(qName);
    domainName = this->findIP(ipName);
    if(domainNam.empty()){
      domainName = redirect2(ipName);
    }
  }

  query.putAll();
  query.putQdCount(1);
  query.putAnCount(1);

  if(ipAddress.empty() && domainName.empty()){
    std::cout<<"\n Name error !! "<<qName<<" Not exist"<<std::endl;
    query.putRData("");
    query.putRCode(DNS_Query::NameError);
    query.putRdLength(1);
  }
  else{
    if(type == 1){
      struct sockaddr_in sa;
      std::string inreverse ;
      for(int i = 0 ; i  < ipAddress.size() ; i++){
        inreverse  = ipAddress[i];
        inreverse = this->ReverseIP(ipAddress);
        inet_pton(AF_INET, inreverse.c_str(), &(sa.sin_addr));
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);
        query.putPrincipalDataA(  sa.sin_addr.s_addr);
        query.putRdLength(4) ;
      }

    }else if(type == 12){
      for(int i = 0 ; i  < domainName.size() ; i++){
        query.putRData(domainName[i]);
        query.putRdLength(domainName[i].size() + 2);
      }
    }
    if(type == 1){
      for(int i = 0 ; i  < ipAddress.size() ; i++){
        printf("\n %d ) Ip Address : %s ",(i+1),ipAddress[i].c_str() );
      }
    }
    if(type == 12){
      for(int i = 0 ; i  < domainName.size() ; i++){
        printf("\n %d ) Domain Name : %s \n",(i+1),domainName[i].c_str() );
      }
    }
    query.putRCode(DNS_Query::Ok);

  }

}
/*=============================================================================================================================*/
std::string DNS::DNS_Resolver::ReverseIP(const std::string& ip) throw() {

  int pos_n = ip.find(".in-addr.arpa");
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
std::vector<std::string> DNS::DNS_Resolver::findIP(std::string ipName){
  std::vector<std::string> temp1 ;
  std::multimap<std::string , std::string > temp ;
  std::multimap<std::string , std::string >::iterator it ;
  std::string stemp ;
  std::pair<std::multimap<std::string,std::string>::iterator,std::multimap<std::string,std::string>::iterator> ret;
  for(it = this->Records.begin() ; it != this->Records.end() ; it++){
    temp.insert(std::pair<std::string , std::string> (it->second , it->first)) ;
  }

  ret = temp.equal_range(ipName);
  for(std::multimap<std::string,std::string>::iterator it2=ret.first;it2!=ret.second && !yes;++it2){
    temp1.push_back(it2->second);
  }
  if (it != temp.end()){
    return temp1 ;
  }else{
    return temp1;
  }
}
/*=============================================================================================================================*/
std::vector<std::string> DNS::DNS_Resolver::redirect(std::string host){
  struct addrinfo* result;
  struct addrinfo* res;
  std::vector<std::string> v;
  char ipstr[INET_ADDRSTRLEN];
  int error;
  error = getaddrinfo(host.c_str(), NULL, NULL, &result);
  if (error != 0) {
      if (error == EAI_SYSTEM) {
        v.push_back("error");
        return v;
      } else {
        v.push_back("error");
        return v;
      }
  }
  std::string aux;
  for (res = result; res != NULL; res = res->ai_next) {
      struct in_addr  *addr;
      if (res->ai_family == AF_INET) {
          struct sockaddr_in *ipv = (struct sockaddr_in *)res->ai_addr;
          addr = &(ipv->sin_addr);
      }
      else {
          struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
          addr = (struct in_addr *) &(ipv6->sin6_addr);
      }
      if(inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr)!=NULL){
        aux =inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);

        v.push_back(aux);
      }
  }
  freeaddrinfo(result);
  return v;
}
/*=============================================================================================================================*/
std::vector<std::string> DNS::DNS_Resolver::redirect2(std::string ipadrr){
  struct addrinfo* result;
  struct addrinfo* res;
  int error;
  std::vector<std::string> v;
  error = getaddrinfo(ipadrr.c_str(), NULL, NULL, &result);
  if (error != 0) {

      if (error == EAI_SYSTEM) {
        v.push_back("error");
        return v;
      } else {
        v.push_back("error");
        return v;
      }

  }
  char hostname[1014];
  for (res = result; res != NULL; res = res->ai_next) {

      char hostname[1025];
      error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, 1025, NULL, 0, 0);
      if (error != 0) {
          continue;
      }
      if (*hostname != '\0'){
        v.push_back(hostname);
      }

  }
  freeaddrinfo(result);
  return v;
}
/*=============================================================================================================================*/
#endif
