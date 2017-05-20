#ifndef _DNS_Resolver_H
#define	_DNS_Resolver_H

#include "readMasterFile.h"

namespace DNS{

class DNS_Resolver{

  public:
    void init(const std::string& filename);

  private:
    std::map<std::string, std::string> masterFile;
  };
}
#include "DNS_Resolver.hxx"

#endif
