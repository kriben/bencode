#include "Bencode.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>

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

void Bencode::tokenize(const std::string& encoded, std::vector<std::string>& tokens)
{
  boost::regex e("([idel])|(\\d+):|(-?\\d+)");
  boost::match_results<std::string::const_iterator> what; 
  boost::match_flag_type flags = boost::match_extra;
  
  int i = 0;
  while (i < static_cast<int>(encoded.size())) {
    std::string current = encoded.substr(i, encoded.size() - i);
    std::cout << "\nChecking: " << current << std::endl;
    if(boost::regex_search(current, what, e, flags)) {
      assert(what.size() == 4);
      std::cout << "FOUND MATCH" << std::endl;
      for(unsigned int j = 0; j < what.size(); ++j) {
	std::cout << "Captures:" << what[i] << std::endl;
	std::cout << "{" << what[j].str() << "}\n";
	
      }

      // 
      if (!what[2].str().empty()) {
	std::istringstream stream(what[2].str());
	int value;
	stream >> value;
	tokens.push_back("s");
	tokens.push_back(current.substr(2, value));
	i += value + 2;
      }
      else {
	tokens.push_back(what[0].str());
       	i += what[0].str().size();
      }
    }
    else {
      i = encoded.size();
    }
  }
}


