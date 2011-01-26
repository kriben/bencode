#ifndef BENCODE_H
#define BENCODE_H

#include <string>
#include <vector>

class Bencode 
{
public:
  static int decodeInt(const std::string& encoded);
  
  static std::string decodeString(const std::string& encoded);

  static void tokenize(const std::string& encoded, std::vector<std::string>& tokens);
  
 private:
  Bencode();

};

#endif
