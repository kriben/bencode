#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer 
{
public:
  static void tokenize(const std::string& encoded, 
		       std::vector<std::string>& tokens);
  
 private:
  Tokenizer();

};

#endif
