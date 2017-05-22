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
std::string DNS::DNS_Resolver::find(std::string domain, unsigned int type){

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
  }else{
    return "error";
  }
}
/*=============================================================================================================================*/
void DNS::DNS_Resolver::process(DNS_Query& query) throw (){
  std::string qName = query.obtainQName();
  std::string ipAddress = "";
  std::string domainName = "";
  unsigned int type = query.obtainQType();

  if(type == 1){

    ipAddress = this->find(qName , 1);
    if(ipAddress=="error"){
      ipAddress= redirect(qName);
    }
  }

  if(type == 12) {

    std::string ipName = this->ReverseIP(qName);
    domainName = this->findIP(ipName);
  }

  query.putAll();
  query.putQdCount(1);
  query.putAnCount(1);


  if(ipAddress == "error" || domainName == "error"){
    std::cout<<"\n Name error !! "<<qName<<" Not exist"<<std::endl;
    query.putRData("");
    query.putRCode(DNS_Query::NameError);
    query.putRdLength(1);
  }
  else{
    printf("\n Domain Name : %s \n",domainName.c_str() );
    printf("\n Domain Name : %s \n",domainName.c_str() );
    if(type == 1){
      struct sockaddr_in sa;
      std::string inreverse = ipAddress ;
      inreverse = this->ReverseIP(ipAddress);
      inet_pton(AF_INET, inreverse.c_str(), &(sa.sin_addr));
      char str[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);
      printf("--- > %u\n",  sa.sin_addr.s_addr);
      query.putPrincipalDataA(  sa.sin_addr.s_addr);

    }else if(type == 12){
      query.putRData(domainName);
    }
    if(type == 1){
      printf("\n Ip Address : %s ",ipAddress.c_str() );
      query.putRdLength(4) ;
    }
    if(type == 12){
      printf("\n Domain Name : %s \n",domainName.c_str() );

      query.putRdLength(domainName.size() + 2);
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
std::string DNS::DNS_Resolver::findIP(std::string ipName){
  std::multimap<std::string , std::string > temp ;
  std::multimap<std::string , std::string >::iterator it ;
  std::string stemp ;
  for(it = this->Records.begin() ; it != this->Records.end() ; it++){
    temp.insert(std::pair<std::string , std::string> (it->second , it->first)) ;
  }
  it = temp.find(ipName);

  if (it != temp.end()){
    return it->second ;
  }else{
    return "error";
  }
}
/*=============================================================================================================================*/
std::string DNS::DNS_Resolver::redirect(std::string host){
  struct addrinfo* result;
  struct addrinfo* res;
  char ipstr[INET_ADDRSTRLEN];
  int error;

  error = getaddrinfo(host, NULL, NULL, &result);
  if (error != 0) {
      if (error == EAI_SYSTEM) {
          return "error";
      } else {
          return "error";
      }
  }
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
      inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
  }
  freeaddrinfo(result);
  return ipstr;
}

#endif
