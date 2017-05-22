#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>

std::vector<std::string> redirect(std::string host){
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
        //printf("hostname: %s\n", inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr));
        v.push_back(aux);
      }
  }
  freeaddrinfo(result);
  return v;
}

std::vector<std::string> redirect2(std::string ipadrr){
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

int main(void)
{
    std::vector<std::string>  v= redirect("google.com");
    std::vector<std::string>::iterator it= v.begin();
    for(;it!=v.end();it++){
      printf("hostname: %s\n", (*it).c_str());
    }
    v= redirect2("216.58.202.238");
    it= v.begin();
    for(;it!=v.end();it++){
      printf("hostname: %s\n", (*it).c_str());
    }
    return 0;
}
