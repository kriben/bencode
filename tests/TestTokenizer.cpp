#include "TestTokenizer.h"
#include "Tokenizer.h"

#include <boost/assign/std/deque.hpp>
#include <stdexcept>

using namespace boost::assign;
using namespace bencode;

void TestTokenizer::testTokenizeInt()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("i3e", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "i", "3", "e";

  verifyTokens(expectedTokens, tokens);
}

void TestTokenizer::testTokenizeNegativeInt()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("i-123e", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "i", "-123", "e";

  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::testTokenizeString()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("4:spam", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "s", "spam";

  verifyTokens(expectedTokens, tokens);
}

void TestTokenizer::testTokenizeLongerString()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("18:Kristian Bendiksen", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "s", "Kristian Bendiksen";

  verifyTokens(expectedTokens, tokens);
}

void TestTokenizer::testTokenizeTooShortString()
{
  std::deque<std::string> tokens;
  CPPUNIT_ASSERT_THROW(Tokenizer::tokenize("4:nei", tokens),
		       std::invalid_argument);
  CPPUNIT_ASSERT(tokens.empty());
}

void TestTokenizer::testTokenizeTooLongString()
{
  std::deque<std::string> tokens;
  CPPUNIT_ASSERT_THROW(Tokenizer::tokenize("2:jepp", tokens),
		       std::invalid_argument);
  CPPUNIT_ASSERT(tokens.empty());
}

void TestTokenizer::testTokenizeList()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("l4:spam4:eggse", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "l", "s", "spam", "s", "eggs", "e";

  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::testTokenizeDict()
{
  std::deque<std::string> tokens;
  Tokenizer::tokenize("d3:cow3:moo4:spam4:eggse", tokens);

  std::deque<std::string> expectedTokens;
  expectedTokens += "d", "s", "cow", "s", "moo", "s", "spam", "s", "eggs", "e";
  verifyTokens(expectedTokens, tokens);
}


void TestTokenizer::verifyTokens(const std::deque<std::string>& expected,
				 const std::deque<std::string>& actual)
{
  CPPUNIT_ASSERT_EQUAL(expected.size(), actual.size());

  for (unsigned int i = 0; i < expected.size(); i++)
    CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
}



CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenizer);
