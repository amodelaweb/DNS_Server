#ifndef __DNS_Query_HXX
#define __DNS_Query_HXX
#include "DNS_Query.h"
void DNS::DNS_Query::decodeQuery(const char* buffer, int size) throw() {
    this->decode_hdr(buffer);
    buffer += HDR_OFFSET;
    this->decode_qname(buffer);
    this->m_qType = this->get16bits(buffer);
    this->m_qClass = this->get16bits(buffer);
}

void DNS::DNS_Query::decode_qname(const char*& buffer) throw() {
    this->m_qName.clear();
    int length = *buffer++;
    while (length != 0) {
        for (int i = 0; i < length; i++) {
            char c = *buffer++;
            this->m_qName.append(1, c);
        }
        length = *buffer++;
        if (length != 0) m_qName.append(1,'.');
    }
}

int DNS::DNS_Query::get16bits(const char*& buffer) throw () {
    int value = static_cast<uchar> (buffer[0]);
    value = value << 8;
    value += static_cast<uchar> (buffer[1]);
    buffer += 2;
    return value;
}

void DNS::DNS_Query::decode_hdr(const char* buffer) throw () {

    this->m_id = get16bits(buffer);

    uint fields = get16bits(buffer);
    this->m_qr = fields & QR_MASK;
    this->m_opcode = fields & OPCODE_MASK;
    this->m_aa = fields & AA_MASK;
    this->m_tc = fields & TC_MASK;
    this->m_rd = fields & RD_MASK;
    this->m_ra = fields & RA_MASK;

    this->m_qdCount = get16bits(buffer);
    this->m_anCount = get16bits(buffer);
    this->m_nsCount = get16bits(buffer);
    this->m_arCount = get16bits(buffer);
}

int DNS::DNS_Query::codeRespose(char* buffer) throw() {

    char* bufferBegin = buffer;

    this->code_hdr(buffer);
    buffer += HDR_OFFSET;

    // Code Question section
    this->code_domain(buffer, m_name);
    this->put16bits(buffer, m_type);
    this->put16bits(buffer, m_class);

    // Code Answer section
    this->code_domain(buffer, m_name);
    this->put16bits(buffer, m_type);
    this->put16bits(buffer, m_class);
    this->put32bits(buffer, m_ttl);
    this->put16bits(buffer, m_rdLength);
    this->code_domain(buffer, m_rdata);

    int size = buffer - bufferBegin;

    return size;
}

void DNS::DNS_Query::code_hdr(char* buffer) throw () {

    this->put16bits(buffer, m_id);

    int fields = (m_qr << 15);
    fields += (m_opcode << 14);
    //...
    fields += m_rcode;
    this->put16bits(buffer, fields);

    this->put16bits(buffer, m_qdCount);
    this->put16bits(buffer, m_anCount);
    this->put16bits(buffer, m_nsCount);
    this->put16bits(buffer, m_arCount);
}

void DNS::DNS_Query::put16bits(char*& buffer, unsigned int value) throw () {

    buffer[0] = (value & 0xFF00) >> 8;
    buffer[1] = value & 0xFF;
    buffer += 2;
}

void DNS::DNS_Query::code_domain(char*& buffer, const std::string& domain) throw() {

    int start(0), end; // indexes

    while ((end = domain.find('.', start)) != string::npos) {

        *buffer++ = end - start; // label length octet
        for (int i=start; i<end; i++) {

            *buffer++ = domain[i]; // label octets
        }
        start = end + 1; // Skip '.'
    }

    *buffer++ = domain.size() - start; // last label length octet
    for (int i=start; i<domain.size(); i++) {

        *buffer++ = domain[i]; // last label octets
    }

    *buffer++ = 0;
}

void DNS::DNS_Query::put32bits(char*& buffer, ulong value) throw () {

    buffer[0] = (value & 0xFF000000) >> 24;
    buffer[1] = (value & 0xFF0000) >> 16;
    buffer[2] = (value & 0xFF00) >> 16;
    buffer[3] = (value & 0xFF) >> 16;
    buffer += 4;
}

#endif
