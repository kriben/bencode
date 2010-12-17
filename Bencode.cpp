#include "Bencode.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <vector>

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

std::string Bencode::decodeString(const std::string& encoded)
{
  if (encoded.empty())
    throw std::invalid_argument("String is empty");

  std::vector<std::string> parts;
  boost::split(parts, encoded, boost::is_any_of(":"));
  if (parts.size() != 2)
    throw std::invalid_argument("Missing colon");
  
  std::istringstream stream(parts[0]);
  int nCharacters;
  stream >> nCharacters;
  if (nCharacters < 0)
    throw std::invalid_argument("Negative string length");

  if (parts[1].size() != static_cast<unsigned int>(nCharacters))
    throw std::invalid_argument("String is incorrectly sized");

  return parts[1];
}

