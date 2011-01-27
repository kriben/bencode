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
  std::vector<std::string> tokens;
  Tokenizer::tokenize(encoded, tokens);

  if (tokens.size() != 2)
    throw std::invalid_argument("Unable to decode");

  if (tokens[0] != "s")
    throw std::invalid_argument("Not a string");

  return tokens[1];
}

