#include "ValueTypes.h"
#include "Decoder.h"
#include "PrettyPrinter.h"

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace bencode;

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Too few arguments: needs a file name..\n";
    return -1;
  }

  std::string filename = argv[1];
  std::ifstream file(filename.c_str());
  if (!file) {
    std::cerr << "Unable to open file: " << filename << "\n";
    return -1;
  }

  std::cout << "Reading " << filename << "\n";
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  try {
    Value torrent =
      boost::get<ValueDictionary>(Decoder::decode(buffer.str()));
    boost::apply_visitor(PrettyPrinter(), torrent);
  }
  catch (std::invalid_argument& e) {
    std::cerr << "An error occurred: " << e.what() << "\n";
    return -1;
  }

  return 0;
}
