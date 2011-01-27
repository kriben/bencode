#include "Tokenizer.h"

#include <boost/regex.hpp>

#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>


void Tokenizer::tokenize(const std::string& encoded, 
			 std::vector<std::string>& tokens)
{
  boost::regex e("([idel])|(\\d+):|(-?\\d+)");
  boost::match_results<std::string::const_iterator> what; 
  boost::match_flag_type flags = boost::match_extra;
  
  int i = 0;
  while (i < static_cast<int>(encoded.size())) {
    std::string current = encoded.substr(i, encoded.size() - i);
    //    std::cout << "\nChecking: " << current << std::endl;
    if(boost::regex_search(current, what, e, flags)) {
      assert(what.size() == 4);
      // std::cout << "FOUND MATCH" << std::endl;
      // for(unsigned int j = 0; j < what.size(); ++j) {
      // 	std::cout << "Captures:" << what[i] << std::endl;
      // 	std::cout << "{" << what[j].str() << "}\n";
      // }

      if (!what[2].str().empty()) {
	std::istringstream stream(what[2].str());
	unsigned int size = what[2].str().size() + 1; // + 1 for the colon
	unsigned int value;
	stream >> value;
	tokens.push_back("s");
	if (size + value > current.size())
	  throw std::invalid_argument("Incorrectly sized string");

	tokens.push_back(current.substr(size, value));
	i += value + size;
      }
      else {
	tokens.push_back(what[0].str());
       	i += what[0].str().size();
      }
    }
    else {
      throw std::invalid_argument("Invalid formatted input.");
    }
  }
}


