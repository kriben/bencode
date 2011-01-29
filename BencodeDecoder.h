#ifndef BENCODEDECODER_H
#define BENCODEDECODER_H

#include "ValueTypes.h"

#include <string>


class BencodeDecoder 
{
public:
  static Value decode(const std::string& encoded);
  
 private:
  BencodeDecoder();

};

#endif
