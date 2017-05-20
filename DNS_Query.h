#ifndef _DNS_QUERY_H
#define	_DNS_QUERY_H

#include <string>

#define QR_MASK 0x8000;
#define OPCODE_MASK 0x7800;
#define AA_MASK 0x0400;
#define TC_MASK 0x0200;
#define RD_MASK 0x0100;
#define RA_MASK 0x8000;
#define RCODE_MASK 0x000F;
#define HDR_OFFSET 12;

namespace DNS{

class DNS_Query{

  public:
    enum Code { Ok=0, FormatError, ServerFailure, NameError,
                NotImplemented, Refused };

    void decodeQuery(const char* buffer, int size) throw();
    void decode_hdr(const char* buffer) throw ();

    int codeRespose(char* buffer) throw();

    int get16bits(const char*& buffer) throw();
    void put16bits(char*& buffer, unsigned int value) throw ();
    void put32bits(char*& buffer, unsigned long value) throw ();

    const std::string& getQName() const throw () { return m_qName; }
    const unsigned int getQType() const throw () { return m_qType; }
    const unsigned int getQClass() const throw () { return m_qClass; }

    void setRCode(Code code) throw() { m_rcode = code; }
    void setName(const std::string& value) throw() { m_name = value; }
    void setType(const unsigned int value) throw() { m_type = value; }
    void setClass(const unsigned int value) throw() { m_class = value; }
    void setTtl(const unsigned int value) throw() { m_ttl = value; }
    void setRdLength(const unsigned int value) throw() { m_rdLength = value; }
    void setRdata(const std::string& value) throw() { m_rdata = value; }

  private:
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

  };
}
#include "DNS_Server.hxx"

#endif
