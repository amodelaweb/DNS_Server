#ifndef _DNS_Resolver_H
#define	_DNS_Resolver_H

#include <iostream>
#include <string>
#include <algorithm>

#include "MasterFile.h"
#include "DNS_Query.h"

namespace DNS{
/*
* Representa un resolver que envía peticiones para obtener
* información y luego se pregunta así mismo si la dicha
* información ya la posee.
*/
class DNS_Resolver{

  public:
    bool init( std::string& filename);
    void process(DNS_Query& query) throw ();
    std::string find(std::string domain, unsigned int type);
    std::string ReverseIP(const std::string& ip) throw();
    std::string findIP(std::string ipName);
    std::string redirect(std::string host);

  private:
    std::multimap<std::string, std::string> Records;
  };
}
#include "DNS_Resolver.hxx"

#endif
