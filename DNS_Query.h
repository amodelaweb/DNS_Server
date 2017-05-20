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
#define MASK_16 0xFF00;
#define MASK_16_2 0xFF ;
#define MASK_32 0xFF000000 ;
#define MASK_32_2 0xFF0000 ;
#define MASK_32_3 0xFF00 ;
#define MASK_32_4 0xFF ;

namespace DNS{

/*
* Representa la petición que realiza el usuario para su respectiva resolución de dominio
* a una dirección IP.
*/

class DNS_Query{

  public:


    enum Code { Ok=0, FormatError, ServerFailure, NameError,
                NotImplemented, Refused };

    void decodeQ(const char* buffer, int size) throw();
    void decodeheader(const char* buffer) throw ();
    unsigned int getQType(); 

    int resposeCode(char* buffer) throw();
    void codeheader(char* buffer) throw ();

    int get16bitEncode(const char*& buffer) throw();
    void putin16bit(char*& buffer, unsigned int value) throw ();
    void putin32bit(char*& buffer, unsigned long value) throw ();

    const std::string& obtainQName() const throw () { return queryName; }
    const unsigned int obtainQType() const throw () { return queryType; }
    const unsigned int obtainQClass() const throw () { return queryClass; }

    void putRCode(Code code) throw() { headerRcode = code; }
    void putName(const std::string& value) throw() { principalName = value; }
    void putType(const unsigned int value) throw() { principalType = value; }
    void putClass(const unsigned int value) throw() { principalClass = value; }
    void putTtl(const unsigned int value) throw() { principalTtl = value; }
    void putRdLength(const unsigned int value) throw() { principalrdLength = value; }
    void putRdata(const std::string& value) throw() { principalrData = value; }

  private:
    std::string queryName;
    unsigned int queryType;
    unsigned int queryClass;
    void decodeQueryName(const char*& buffer) throw();

    std::string principalName;
    unsigned int principalType;
    unsigned int principalClass;
    unsigned long principalTtl;
    unsigned int principalrdLength;
    std::string principalrData;
    void codedomain(char*& buffer, const std::string& domain) throw();

    unsigned int headerid;
    unsigned int headerQr;
    unsigned int headerOpCode;
    unsigned int headerAa;
    unsigned int headerTc;
    unsigned int headerRd;
    unsigned int headerRa;
    unsigned int headerRcode;

    unsigned int headerQdCount;
    unsigned int headerAnCount;
    unsigned int headerNsCount;
    unsigned int headerArCount;


    void setRCode(Code code) throw() { this->m_rcode = code; }
    void setRdLength(const unsigned int value) throw() { this->m_rdLength = value; }
    void setRdata(const std::string& value) throw() { this->m_rdata = value; }

    unsigned int getID() const throw() { return m_id; }
    unsigned int getQdCount() const throw() { return m_qdCount; }
    unsigned int getAnCount() const throw() { return m_anCount; }
    unsigned int getNsCount() const throw() { return m_nsCount; }
    unsigned int getArCount() const throw() { return m_arCount; }

    void setID(unsigned int id) throw() { m_id = id; }
    void setQdCount(unsigned int count) throw() { this->m_qdCount = count; }
    void setAnCount(unsigned int count) throw() { this->m_anCount = count; }
    void setNsCount(unsigned int count) throw() { this->m_nsCount = count; }
    void setArCount(unsigned int count) throw() { this->m_arCount = count; }

  private:
    std::string m_qName;
    unsigned int q_Type;
    unsigned int m_qClass;
    void decode_qname(const char*& buffer) throw();

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

    void putRCode(Code code) throw() { this->m_rcode = code; }
    void putRdLength(const unsigned int value) throw() { this->m_rdLength = value; }
    void putRData(const std::string& value) throw() { this->m_rdata = value; }

    unsigned int obtainID() const throw() { return m_id; }
    unsigned int obtainQdCount() const throw() { return m_qdCount; }
    unsigned int obtainAnCount() const throw() { return m_anCount; }
    unsigned int obtainNsCount() const throw() { return m_nsCount; }
    unsigned int obtainArCount() const throw() { return m_arCount; }

    void putID(unsigned int id) throw() { m_id = id; }
    void putQdCount(unsigned int count) throw() { this->m_qdCount = count; }
    void putAnCount(unsigned int count) throw() { this->m_anCount = count; }
    void putNsCount(unsigned int count) throw() { this->m_nsCount = count; }


  };
}
#include "DNS_Query.hxx"

#endif
