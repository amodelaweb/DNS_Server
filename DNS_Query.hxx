#ifndef __DNS_Query_HXX
#define __DNS_Query_HXX

#include "DNS_Query.h"


/*=============================================================================================================================*/
void DNS::DNS_Query::decodeQ(const char* buffer, int size) throw() {
  this->decodeheader(buffer);
  buffer += HDR_OFFSET;
  this->decodeQueryName(buffer);
  this->queryType = this->get16bitEncode(buffer);
  this->queryClass = this->get16bitEncode(buffer);
}
/*=============================================================================================================================*/
void DNS::DNS_Query::decodeQueryName(const char*& buffer) throw() {
  this->queryName.clear();
  int length = *buffer++;
  while (length != 0) {
    for (int i = 0; i < length; i++) {
      char c = *buffer++;
      this->queryName.append(1, c);
    }
    length = *buffer++;
    if (length != 0)
    this->queryName.append(1,'.');
  }
}
/*=============================================================================================================================*/
int DNS::DNS_Query::get16bitEncode(const char*& buffer) throw () {
  int value = static_cast<unsigned char> (buffer[0]);
  value = value << 8;
  value += static_cast<unsigned char> (buffer[1]);
  buffer += 2;
  return value;
}
/*=============================================================================================================================*/
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
/*=============================================================================================================================*/
int DNS::DNS_Query::resposeCode(char* buffer) throw() {

  char* begin = buffer;

  this->codeheader(buffer);

  buffer += HDR_OFFSET;

  this->encodeResponse(buffer, principalName);
  this->putin16bit(buffer, principalType);
  this->putin16bit(buffer, principalClass);



  if(principalType == 1 ){
    for(int i = 0 ; i < this->principalrDataA.size() ; i++ ){

      this->encodeResponse(buffer, principalName);
      this->putin16bit(buffer, principalType);
      this->putin16bit(buffer, principalClass);
      this->putin32bit(buffer, principalTtl);
      this->putin16bit(buffer, this->principalrdLength[i]);
      this->putin32bit(buffer , this->principalrDataA[i]);
    }
  }

  if(principalType == 12){
    for(int i = 0 ; i < this->principalrData.size() ; i++){
      this->encodeResponse(buffer, principalName);
      this->putin16bit(buffer, principalType);
      this->putin16bit(buffer, principalClass);
      this->putin32bit(buffer, principalTtl);
      this->putin16bit(buffer, principalrdLength[i]);
      this->encodeResponse(buffer, principalrData[i]);
    }
  }
  int size = buffer - begin;

  return size;
}
/*=============================================================================================================================*/
void DNS::DNS_Query::codeheader(char* buffer) throw () {

  this->putin16bit(buffer, this->headerid);

  unsigned int fields = ((1) << 15);
  fields += (this->headerOpCode << 14);
  fields += (this->headerAa << 13);
  fields += (this->headerTc <<12);
  fields += (this->headerRd <<11);
  fields += (this->headerRa <<10);
  fields += ( 0 <<10);
  fields += ( 0 << 9);
  fields += ( 0 <<8);
  fields += ( 0 <<7);
  fields += ( 0 <<6);
  fields += ( 0 <<5);
  fields += ( 0 <<4);
  fields += ( 0 <<3);
  fields += ( 0 <<2);
  fields += this->headerRcode;
  this->putin16bit(buffer, fields);

  this->putin16bit(buffer, this->headerQdCount);
  this->putin16bit(buffer, this->headerAnCount);
  this->putin16bit(buffer, 0); //Ar
  this->putin16bit(buffer, 0); //NS
}

/*=============================================================================================================================*/
void DNS::DNS_Query::putin16bit(char*& buffer, unsigned int value) throw () {

  buffer[0] = (unsigned char)(value>>8);
  buffer[1] = value & 0xff;
  buffer += 2;
}
/*=============================================================================================================================*/
void DNS::DNS_Query::encodeResponse(char*& buffer, const std::string& response) throw() {

  int start(0), end;

  while ((end = response.find('.', start)) != std::string::npos) {

    *buffer++ = end - start;
    for (int i=start; i<end; i++) {

      *buffer++ = response[i];
    }
    start = end + 1;
  }

  *buffer++ = response.size() - start;
  for (int i=start; i<response.size(); i++){
    *buffer++ = response[i];
  }


  *buffer++ = 0;
}
/*=============================================================================================================================*/
void DNS::DNS_Query::putin32bit(char*& buffer, unsigned long value) throw () {

  buffer[0] = (value & 0xff000000UL) >> 24;
  buffer[1] =(value & 0x00ff0000UL) >> 16;
  buffer[2] =  (value & 0x0000ff00UL) >>  8;
  buffer[3] = (value & 0x000000ffUL)      ;

  buffer += 4;
}
/*=============================================================================================================================*/
void DNS::DNS_Query::putAll(){
  this->principalID = this->headerid ;
  this->principalName = this->queryName ;
  this->principalType = this->queryType ;
  this->principalClass = this->queryClass ;
}
#endif
