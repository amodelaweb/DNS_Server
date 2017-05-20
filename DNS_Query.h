#ifndef _DNS_QUERY_H
#define	_DNS_QUERY_H

#include <string>

namespace DNS{
  class Query{
  public:
    int get16bits(const char*& buffer) throw();
    void put16bits(char*& buffer, uint value) throw ();
    void put32bits(char*& buffer, ulong value) throw ();
    std::string asStringRespose() const throw();
    std::string asStringQuery() const throw();
  private:
    std::string query_name ;
    unsigned int q_type ;
    unsigned int q_class ;
    std::string m_rdata;
    static const uint QR_MASK = 0x8000;
    static const uint OPCODE_MASK = 0x7800;
    static const uint AA_MASK = 0x0400;
    static const uint TC_MASK = 0x0200;
    static const uint RD_MASK = 0x0100;
    static const uint RA_MASK = 0x8000;
    static const uint RCODE_MASK = 0x000F;
  };
}
#include "DNS_Server.hxx"

#endif
