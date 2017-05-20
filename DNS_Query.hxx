#ifndef __DNS_Query_HXX
#define __DNS_Query_HXX

#include "DNS_Query.h"

void DNS::DNS_Query::decodeQ(const char* buffer, int size) throw() {
    this->decodeheader(buffer);
    buffer += HDR_OFFSET;
    this->decodeQueryName(buffer);
    this->queryType = this->get16bitEncode(buffer);
    this->queryClass = this->get16bitEncode(buffer);
}

void DNS::DNS_Query::decodeQueryName(const char*& buffer) throw() {
    this->queryName.clear();
    int length = *buffer++;
    while (length != 0) {
        for (int i = 0; i < length; i++) {
            char c = *buffer++;
            this->queryName.append(1, c);
        }
        length = *buffer++;
        if (length != 0) queryName.append(1,'.');
    }
}

int DNS::DNS_Query::get16bitEncode(const char*& buffer) throw () {
    int value = static_cast<unsigned char> (buffer[0]);
    value = value << 8;
    value += static_cast<unsigned char> (buffer[1]);
    buffer += 2;
    return value;
}

void DNS::DNS_Query::decodeheader(const char* buffer) throw () {

    this->headerid = get16bitEncode(buffer);

    unsigned int fields = get16bitEncode(buffer);
    this->headerQr = fields & QR_MASK;
    this->headerOpCode = fields & OPCODE_MASK;
    this->headerAa = fields & AA_MASK;
    this->headerTc = fields & TC_MASK;
    this->headerRd = fields & RD_MASK;
    this->headerRa = fields & RA_MASK;

    this->headerQdCount = get16bitEncode(buffer);
    this->headerAnCount = get16bitEncode(buffer);
    this->headerNsCount = get16bitEncode(buffer);
    this->headerArCount = get16bitEncode(buffer);
}

int DNS::DNS_Query::resposeCode(char* buffer) throw() {

    char* bufferBegin = buffer;

    this->codeheader(buffer);
    buffer += HDR_OFFSET;

    this->codedomain(buffer, principalName);
    this->put16bit(buffer, principalType);
    this->put16bit(buffer, principalClass);

    this->codedomain(buffer, principalName);
    this->put16bit(buffer, principalType);
    this->put16bit(buffer, principalClass);
    this->put32bit(buffer, principalTtl);
    this->put16bit(buffer, principalrdLength);
    this->codedomain(buffer, principalrData);
    this->code_domain(buffer, m_qName);
    this->put16bits(buffer, m_qType);
    this->put16bits(buffer, m_qClass);

    this->code_domain(buffer, m_qName);
    this->put16bits(buffer, m_qType);
    this->put16bits(buffer, m_qClass);
    this->put32bits(buffer, m_ttl);
    this->put16bits(buffer, m_rdLength);
    this->code_domain(buffer, m_rdata);

    int size = buffer - bufferBegin;

    return size;
}

void DNS::DNS_Query::codeheader(char* buffer) throw () {

    this->put16bit(buffer, headerid);

    int fields = (headerQr << 15);
    fields += (headerOpCode << 14);
    //...
    fields += headerRcode;
    this->put16bit(buffer, fields);

    this->put16bit(buffer, headerQdCount);
    this->put16bit(buffer, headerAnCount);
    this->put16bit(buffer, headerNsCount);
    this->put16bit(buffer, headerArCount);
}

void DNS::DNS_Query::put16bit(char*& buffer, unsigned int value) throw () {

    buffer[0] = (value & 0xFF00) >> 8;
    buffer[1] = value & 0xFF;
    buffer += 2;
}

void DNS::DNS_Query::codedomain(char*& buffer, const std::string& domain) throw() {

    int start(0), end;

    while ((end = domain.find('.', start)) != std::string::npos) {

        *buffer++ = end - start;
        for (int i=start; i<end; i++) {

            *buffer++ = domain[i];
        }
        start = end + 1;
    }

    *buffer++ = domain.size() - start;
    for (int i=start; i<domain.size(); i++) {

        *buffer++ = domain[i];
    }

    *buffer++ = 0;
}

void DNS::DNS_Query::put32bit(char*& buffer, unsigned long value) throw () {

    buffer[0] = (value & 0xFF000000) >> 24;
    buffer[1] = (value & 0xFF0000) >> 16;
    buffer[2] = (value & 0xFF00) >> 16;
    buffer[3] = (value & 0xFF) >> 16;
    buffer += 4;
}

#endif
