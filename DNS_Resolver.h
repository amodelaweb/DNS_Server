#ifndef _DNS_Resolver_H
#define	_DNS_Resolver_H

#include "readMasterFile.h"
#include "DNS_Query.h"

namespace DNS{
/*
* Representa un resolver que envía peticiones para obtener
* información y luego se pregunta así mismo si la dicha
* información ya la posee.
*/
class DNS_Resolver{

  public:
    void init(const std::string& filename);
    void process(DNS_Query& query) throw ();
    std::string find(std::string domain, std::string type);

  private:
    std::map<std::string, std::string> masterFile;
  };
}
#include "DNS_Resolver.hxx"

#endif
