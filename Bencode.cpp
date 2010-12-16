#include "Bencode.h"

#include <cassert>
#include <sstream>

int Bencode::decodeInt(const std::string& encoded)
{
  // TODO: check if the first letter is "i"
  assert(!encoded.empty());
  assert(encoded[0] == 'i');
  
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

