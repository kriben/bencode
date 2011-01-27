#include "Bencode.h"
#include "Tokenizer.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <vector>


int Bencode::decodeInt(const std::string& encoded)
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize(encoded, tokens);
  
  if (tokens.size() < 3)
    throw std::invalid_argument("Encoded data is too short");

  if (tokens[0] != "i")
    throw std::invalid_argument("Incorrect encoding: does not start with 'i'");

  if (tokens[2] != "e")
    throw std::invalid_argument("Incorrect encoding: does not end with 'e'");

  if (tokens[1] == "-0")
    throw std::invalid_argument("Negative zero is not allowed");
  
  std::istringstream stream(tokens[1]);
  int value;
  stream >> value;
    
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

