#ifndef _DNS_QUERY_H
#define	_DNS_QUERY_H

#include <string>

namespace DNS{

class Query{

  public:
    void decodeQuery(const char* buffer, int size) throw();
    void decode_hdr(const char* buffer) throw ();
    std::string asStringQuery() const throw();

    int codeRespose(char* buffer) throw();
    std::string asStringRespose() const throw();
    
    int get16bits(const char*& buffer) throw();
    void put16bits(char*& buffer, unsigned int value) throw ();
    void put32bits(char*& buffer, unsigned long value) throw ();

  private:
    static const unsigned int HDR_OFFSET = 12;
    std::string m_qName;
    unsigned int m_qType;
    unsigned int m_qClass;
    void decode_qname(const char*& buffer) throw();

    std::string m_name;
    unsigned int m_type;
    unsigned int m_class;
    unsigned long m_ttl;
    unsigned int m_rdLength;
    std::string m_rdata;
    void code_domain(char*& buffer, const std::string& domain) throw();

    unsigned int m_id;
    unsigned int m_qr;
    unsigned int m_opcode;
    unsigned int m_aa;
    unsigned int m_tc;
    unsigned int m_rd;
    unsigned int m_ra;
    unsigned int m_rcode;

    unsigned int m_qdCount;
    unsigned int m_anCount;
    unsigned int m_nsCount;
    unsigned int m_arCount;

    static const unsigned int QR_MASK = 0x8000;
    static const unsigned int OPCODE_MASK = 0x7800;
    static const unsigned int AA_MASK = 0x0400;
    static const unsigned int TC_MASK = 0x0200;
    static const unsigned int RD_MASK = 0x0100;
    static const unsigned int RA_MASK = 0x8000;
    static const unsigned int RCODE_MASK = 0x000F;
  };
}
#include "DNS_Server.hxx"

#endif
