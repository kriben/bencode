#include "BencodeDecoder.h"
#include "Tokenizer.h"

#include <boost/lexical_cast.hpp>

#include <stdexcept>
#include <vector>


Value BencodeDecoder::decode(const std::string& encoded)
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize(encoded, tokens);
  if (tokens.size() < 3)
    throw std::invalid_argument("Encoded data is too short");

  if (tokens[0] == "i") {
    if (tokens[2] != "e") 
      throw std::invalid_argument("Incorrect encoding: does not end with 'e'");

    if (tokens[1] == "-0")
      throw std::invalid_argument("Negative zero is not allowed");

    try {
      int value = boost::lexical_cast<int>(tokens[1]);
      return Value(value);
    }
    catch (boost::bad_lexical_cast&) {
      throw std::invalid_argument("Incorrect integer: " + tokens[1]);
    }
  }

  return Value(0);
}

