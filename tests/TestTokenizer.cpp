#include "TestTokenizer.h"
#include "Tokenizer.h"

#include <boost/assign/std/vector.hpp>
#include <stdexcept>

using namespace boost::assign;
using namespace bencode;

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

void TestTokenizer::testTokenizeLongerString()
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize("18:Kristian Bendiksen", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens += "s", "Kristian Bendiksen";

  verifyTokens(expectedTokens, tokens);
}

void TestTokenizer::testTokenizeTooShortString()
{
  std::vector<std::string> tokens;
  CPPUNIT_ASSERT_THROW(Tokenizer::tokenize("4:nei", tokens),
		       std::invalid_argument);
  CPPUNIT_ASSERT(tokens.empty());
}

void TestTokenizer::testTokenizeTooLongString()
{
  std::vector<std::string> tokens;
  CPPUNIT_ASSERT_THROW(Tokenizer::tokenize("2:jepp", tokens),
		       std::invalid_argument);
  CPPUNIT_ASSERT(tokens.empty());
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

  for (unsigned int i = 0; i < std::max(actual.size(), expected.size()); i++)
    CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
}



CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenizer);
