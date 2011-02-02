#ifndef ENCODER_H
#define ENCODER_H

#include "ValueTypes.h"

#include <string>

class Encoder
{
public:
  static std::string encode(const Value& value);

 private:

  Encoder();

};

#endif
