#ifndef BENCODE_TOKENIZER_H
#define BENCODE_TOKENIZER_H

#include <string>
#include <deque>

namespace bencode {

  class Tokenizer
  {
  public:
    static void tokenize(const std::string& encoded,
			 std::deque<std::string>& tokens);

  private:
    Tokenizer();
  };

};

#endif
