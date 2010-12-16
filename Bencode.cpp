#include "Bencode.h"

#include <cassert>
#include <sstream>
#include <stdexcept>

int Bencode::decodeInt(const std::string& encoded)
{
  if (encoded.size() < 3)
    throw std::invalid_argument("Encoded data is too short");

  if (encoded[0] != 'i')
    throw std::invalid_argument("Incorrect encoding: does not start with 'i'");

  if (encoded[encoded.size() - 1] != 'e')
    throw std::invalid_argument("Incorrect encoding: does not end with 'e'");
  
  int length = 0;
  int i = 1;
  bool isNegative = false;
  while (encoded[i] == '-' || (encoded[i] >= '0' && encoded[i] <= '9')) {
    if (encoded[i] == '-') {
      // Multiple minus signes are not allowed
      if (isNegative)
	throw std::invalid_argument("Multiple '-' signs found");
      isNegative = true;
    }
    
    i++;
    length++;
  }

  std::istringstream stream(encoded.substr(1, length));
  int value;
  stream >> value;

  if (value == 0 && isNegative)
    throw std::invalid_argument("Negative zero is not allowed");
    
  return value;
}

