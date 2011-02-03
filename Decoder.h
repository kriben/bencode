#ifndef DECODER_H
#define DECODER_H

#include "ValueTypes.h"

#include <string>
#include <deque>

namespace bencode {

  class Decoder
  {
  public:
    static Value decode(const std::string& encoded);

  private:
    static Value decode(std::deque<std::string>& tokens);

    static Value decodeInteger(std::deque<std::string>& tokens);

    static Value decodeString(std::deque<std::string>& tokens);

    static Value decodeVector(std::deque<std::string>& tokens);

    static Value decodeDictionary(std::deque<std::string>& tokens);

    Decoder();
  };
};

#endif
