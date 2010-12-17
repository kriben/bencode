#ifndef BENCODE_H
#define BENCODE_H

#include <string>

class Bencode 
{
public:
  static int decodeInt(const std::string& encoded);
  
  static std::string decodeString(const std::string& encoded);

private:
  Bencode();

};

#endif
