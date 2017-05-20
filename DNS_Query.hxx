#ifndef __DNS_Query_HXX
#define __DNS_Query_HXX

void DNS_Query::decode(const char* buffer, int size) throw() {
    decode_hdr(buffer);
    buffer += HDR_OFFSET;
    decode_qname(buffer);
    m_qType = this->get16bits(buffer);
    m_qClass = this->get16bits(buffer);
}

void DNS_Query::decode_qname(const char*& buffer) throw() {
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

int DNS_Query::get16bits(const char*& buffer) throw () {
    int value = static_cast<uchar> (buffer[0]);
    value = value << 8;
    value += static_cast<uchar> (buffer[1]);
    buffer += 2;
    return value;
}

void DNS_Query::decode_hdr(const char* buffer) throw () {

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

#endif
