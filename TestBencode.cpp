#include "TestBencode.h"
#include "Bencode.h"

#include <stdexcept>

void TestBencode::testDecodeLegalInts()
{
  CPPUNIT_ASSERT_EQUAL(0, Bencode::decodeInt("i0e"));
  CPPUNIT_ASSERT_EQUAL(1, Bencode::decodeInt("i1e"));
  CPPUNIT_ASSERT_EQUAL(10, Bencode::decodeInt("i10e"));
  CPPUNIT_ASSERT_EQUAL(43, Bencode::decodeInt("i43e"));
  CPPUNIT_ASSERT_EQUAL(123456789, Bencode::decodeInt("i123456789e"));

  CPPUNIT_ASSERT_EQUAL(-1, Bencode::decodeInt("i-1e"));
  CPPUNIT_ASSERT_EQUAL(-22, Bencode::decodeInt("i-22e"));
}

void TestBencode::testDecodeIllegalInts()
{
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("ie"), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt(""), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("    "), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i0f"), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i-1-2e"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i-0e"), std::invalid_argument);
}

void TestBencode::testDecodeLegalStrings()
{
  CPPUNIT_ASSERT_EQUAL(std::string("spam"), Bencode::decodeString("4:spam"));
  CPPUNIT_ASSERT_EQUAL(std::string("yes"), Bencode::decodeString("3:yes"));
  CPPUNIT_ASSERT_EQUAL(std::string("Kristian Bendiksen"),
		       Bencode::decodeString("18:Kristian Bendiksen"));
  CPPUNIT_ASSERT_EQUAL(std::string(""), Bencode::decodeString("0:"));
}

void TestBencode::testDecodeIllegalStrings()
{
  CPPUNIT_ASSERT_THROW(Bencode::decodeString(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("spam"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("-2:no"), std::invalid_argument);
}

void TestBencode::testDecodeIncorrectlySizedStrings()
{
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("3:no"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("2:yes"), std::invalid_argument);
}

void TestBencode::testTokenizeInt()
{
  std::vector<std::string> tokens;
  Bencode::tokenize("i3e", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens.push_back("i");
  expectedTokens.push_back("3");
  expectedTokens.push_back("e");

  verifyTokens(expectedTokens, tokens);
}

void TestBencode::testTokenizeNegativeInt()
{
  std::vector<std::string> tokens;
  Bencode::tokenize("i-123e", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens.push_back("i");
  expectedTokens.push_back("-123");
  expectedTokens.push_back("e");

  verifyTokens(expectedTokens, tokens);
}


void TestBencode::testTokenizeString()
{
  std::vector<std::string> tokens;
  Bencode::tokenize("4:spam", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens.push_back("s");
  expectedTokens.push_back("spam");
  verifyTokens(expectedTokens, tokens);
}



void TestBencode::testTokenizeList()
{
  std::vector<std::string> tokens;
  Bencode::tokenize("l4:spam4:eggse", tokens);

  std::vector<std::string> expectedTokens;
  expectedTokens.push_back("l");
  expectedTokens.push_back("s");
  expectedTokens.push_back("spam");
  expectedTokens.push_back("s");
  expectedTokens.push_back("eggs");
  expectedTokens.push_back("e");

  verifyTokens(expectedTokens, tokens);
}


void TestBencode::verifyTokens(const std::vector<std::string>& expected,
			       const std::vector<std::string>& actual)
{
  std::cout << std::endl;
  for (unsigned int i = 0; i < std::max(actual.size(), expected.size()); i++) {
    std::cout << "[" << i << "]: "
	      << "expected: {";
    if (i < expected.size())
      std::cout << expected[i]; 
    else
      std::cout << "__MISSING__";
    std::cout << "} "
    	      << "actual: {";

    if (i < actual.size())
      std::cout << actual[i];
    else 
      std::cout << "__MISSING__";
    std::cout << "}\n";
    CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
  }

  CPPUNIT_ASSERT_EQUAL(expected.size(), actual.size());
}



CPPUNIT_TEST_SUITE_REGISTRATION(TestBencode);
