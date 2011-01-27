#include "TestTokenizer.h"
#include "Tokenizer.h"

#include <boost/assign/std/vector.hpp>

using namespace boost::assign;


void TestTokenizer::testTokenizeInt()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("i3e", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "i", "3", "e";

  verifyTokens(expectedTokens, tokens);
}

void TestTokenizer::testTokenizeNegativeInt()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("i-123e", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "i", "-123", "e";

  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::testTokenizeString()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("4:spam", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "s", "spam";

  verifyTokens(expectedTokens, tokens);
}



void TestTokenizer::testTokenizeList()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("l4:spam4:eggse", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "l", "s", "spam", "s", "eggs", "e";

  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::testTokenizeDict()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("d3:cow3:moo4:spam4:eggse", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "d", "s", "cow", "s", "moo", "s", "spam", "s", "eggs", "e";
  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::verifyTokens(const std::vector<std::string>& expected,
			       const std::vector<std::string>& actual)
{
  CPPUNIT_ASSERT_EQUAL(expected.size(), actual.size());

  //  std::cout << std::endl;
  for (unsigned int i = 0; i < std::max(actual.size(), expected.size()); i++) {
    // std::cout << "[" << i << "]: "
    // 	      << "expected: {" << expected[i] << "} "
    // 	      << "actual: {" << actual[i] << "}\n";

    CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
  }
}



CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenizer);
