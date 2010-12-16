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

  int first = 1;
  int length = 0;
  int i = first;
  while (encoded[i] == '-' || (encoded[i] >= '0' && encoded[i] <= '9')) {
    i++;
    length++;
  }

  std::istringstream stream(encoded.substr(first, length));
  int value;
  stream >> value;
  return value;
}

