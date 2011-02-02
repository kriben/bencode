#ifndef TESTTOKENIZER_H
#define TESTTOKENIZER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <vector>
#include <string>

class TestTokenizer : public CppUnit::TestFixture
{
public:
  void testTokenizeInt();
  void testTokenizeNegativeInt();
  void testTokenizeString();
  void testTokenizeLongerString();
  void testTokenizeTooShortString();
  void testTokenizeTooLongString();
  void testTokenizeList();
  void testTokenizeDict();
private:
  static void verifyTokens(const std::vector<std::string>& expected,
			   const std::vector<std::string>& actual);

  CPPUNIT_TEST_SUITE(TestTokenizer);
  CPPUNIT_TEST(testTokenizeInt);
  CPPUNIT_TEST(testTokenizeNegativeInt);
  CPPUNIT_TEST(testTokenizeString);
  CPPUNIT_TEST(testTokenizeLongerString);
  CPPUNIT_TEST(testTokenizeTooShortString);
  CPPUNIT_TEST(testTokenizeTooLongString);
  CPPUNIT_TEST(testTokenizeList);
  CPPUNIT_TEST(testTokenizeDict);
  CPPUNIT_TEST_SUITE_END();
};

#endif
