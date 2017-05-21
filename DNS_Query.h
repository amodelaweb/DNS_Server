#ifndef _DNS_QUERY_H
#define	_DNS_QUERY_H

#include <string>

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
    void putRCode(Code code) throw() { this->headerRcode = code; }
    void putRdLength(const unsigned int value) throw() { this->principalrdLength = value; }
    void putRData(const std::string& value) throw() { this->principalrData = value; }

    unsigned int obtainQueryType(){ return queryType}
    unsigned int obtainID() const throw() { return headerid; }
    unsigned int obtainQdCount() const throw() { return headerQdCount; }
    unsigned int obtainAnCount() const throw() { return headerAnCount; }
    unsigned int obtainNsCount() const throw() { return headerNsCount; }
    unsigned int obtainArCount() const throw() { return headerArCount; }

    void putID(unsigned int id) throw() { headerid = id; }
    void putQdCount(unsigned int count) throw() { this->headerQdCount = count; }
    void putAnCount(unsigned int count) throw() { this->headerAnCount = count; }
    void putNsCount(unsigned int count) throw() { this->headerNsCount = count; }
    void putArCount(unsigned int count) throw() { this->headerArCount = count; }

    void setRCode(Code code) throw() { this->headerRcode = code; }
    void setRdLength(const unsigned int value) throw() { this->principalrdLength = value; }
    void setRdata(const std::string& value) throw() { this->principalrData = value; }
<<<<<<< HEAD

    unsigned int getID() const throw() { return headerid; }
    unsigned int getQdCount() const throw() { return headerQdCount; }
    unsigned int getAnCount() const throw() { return headerAnCount; }
    unsigned int getNsCount() const throw() { return headerNsCount; }
    unsigned int getArCount() const throw() { return headerArCount; }

=======

    unsigned int getID() const throw() { return headerid; }
    unsigned int getQdCount() const throw() { return headerQdCount; }
    unsigned int getAnCount() const throw() { return headerAnCount; }
    unsigned int getNsCount() const throw() { return headerNsCount; }
    unsigned int getArCount() const throw() { return headerArCount; }

>>>>>>> b5d513e58f46e92c3887e8cceda2e3e5fd8d2526
    void setID(unsigned int id) throw() { headerid = id; }
    void setQdCount(unsigned int count) throw() { this->headerQdCount = count; }
    void setAnCount(unsigned int count) throw() { this->headerAnCount = count; }
    void setNsCount(unsigned int count) throw() { this->headerNsCount = count; }
    void setArCount(unsigned int count) throw() { this->headerArCount = count; }

  };
}
#include "DNS_Query.hxx"

#endif
/*=============================================================================================================================*/
