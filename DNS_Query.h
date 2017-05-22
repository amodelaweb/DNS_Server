#ifndef _DNS_QUERY_H
#define	_DNS_QUERY_H

#include <string>
#include <vector>

#define QR_MASK 0x8000
#define OPCODE_MASK 0x7800
#define AA_MASK 0x0400
#define TC_MASK 0x0200
#define RD_MASK 0x0100
#define RA_MASK 0x8000
#define RCODE_MASK 0x000F
#define HDR_OFFSET 12
#define MASK16 0xFF00
#define MASK16_1 0xFF
#define MASK32 0xFF000000
#define MASK32_1 0xFF0000
#define MASK32_2 0xFF00
#define MASK32_3 0xFF
namespace DNS{

/*
* Representa la petición que realiza el usuario para su respectiva resolución de dominio
* a una dirección IP.
*/

class DNS_Query{

  public:
    DNS_Query(){}
    enum Code { Ok=0, FormatError, ServerFailure, NameError,
                NotImplemented, Refused };
    void decodeQ(const char* buffer, int size) throw();
    void decodeheader(const char* buffer) throw ();

    int resposeCode(char* buffer) throw();
    void codeheader(char* buffer) throw ();

    int get16bitEncode(const char*& buffer) throw();
    void putin16bit(char*& buffer, unsigned int value) throw ();
    void putin32bit(char*& buffer, unsigned long value) throw ();

    const std::string& obtainQName() const throw () { return queryName; }
    const unsigned int obtainQType() const throw () { return queryType; }
    const unsigned int obtainQClass() const throw () { return queryClass; }
    void putAll();

    void putRCode(Code code) throw() { this->headerRcode = code; }
    void putRdLength(const unsigned int value) throw() { this->principalrdLength.push_back(value); }
    void putRData(const std::string& value) throw() { this->principalrData.push_back(value); }

    unsigned int obtainQueryType(){ return queryType;}
    unsigned int obtainID() const throw() { return headerid; }
    unsigned int obtainQdCount() const throw() { return headerQdCount; }
    unsigned int obtainAnCount() const throw() { return headerAnCount; }
    unsigned int obtainNsCount() const throw() { return headerNsCount; }
    unsigned int obtainArCount() const throw() { return headerArCount; }

    void putQdCount(unsigned int count) throw() { this->headerQdCount = count; }
    void putAnCount(unsigned int count) throw() { this->headerAnCount = count; }
    void putNsCount(unsigned int count) throw() { this->headerNsCount = count; }
    void putArCount(unsigned int count) throw() { this->headerArCount = count; }
    void putPrincipalDataA(unsigned long data) throw() { this->principalrDataA.push_back(data) ; }

    void decodeQueryName(const char*& buffer) throw();
    void encodeResponse(char*& buffer, const std::string& response) throw();

  private:

    std::string queryName;
    unsigned int queryType;
    unsigned int queryClass;


    std::string principalName;
    unsigned int principalID ;
    unsigned int principalType;
    unsigned int principalClass;
    unsigned long principalTtl = (unsigned long) 150;
    std::vector<unsigned int> principalrdLength;
    std::vector<std::string> principalrData ;
    std::vector<unsigned long> principalrDataA ;
    unsigned int headerid;
    unsigned int headerQr;
    unsigned int headerOpCode : 4;
    unsigned int headerAa : 1;
    unsigned int headerTc : 1;
    unsigned int headerRd;
    unsigned int headerRa : 1;
    unsigned int headerRcode;

    const char* buffertemp ;
    unsigned int headerQdCount = 0;
    unsigned int headerAnCount = 0 ;
    unsigned int headerNsCount = 0 ;
    unsigned int headerArCount = 0;


  };
}
#include "DNS_Query.hxx"

#endif
/*=============================================================================================================================*/
