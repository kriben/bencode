#ifndef BENCODEDECODER_H
#define BENCODEDECODER_H

#include "ValueTypes.h"

#include <string>
#include <deque>


class BencodeDecoder
{
public:
  static Value decode(const std::string& encoded);

 private:
  static Value decode(std::deque<std::string>& tokens);

  BencodeDecoder();

};

#endif
