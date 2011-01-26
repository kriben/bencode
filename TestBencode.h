#ifndef TESTBENCODE_H
#define TESTBENCODE_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <vector>
#include <string>

class TestBencode : public CppUnit::TestFixture
{
public:
  void testDecodeLegalInts();
  void testDecodeIllegalInts();
  void testDecodeLegalStrings();
  void testDecodeIllegalStrings();
  void testDecodeIncorrectlySizedStrings();
  void testTokenizeInt();
  void testTokenizeNegativeInt();
  void testTokenizeString();
  void testTokenizeList();
private:
  static void verifyTokens(const std::vector<std::string>& expected,
			   const std::vector<std::string>& actual);

  CPPUNIT_TEST_SUITE(TestBencode);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST(testDecodeLegalStrings);
  CPPUNIT_TEST(testDecodeIllegalStrings);
  CPPUNIT_TEST(testDecodeIncorrectlySizedStrings);
  CPPUNIT_TEST(testTokenizeInt);
  CPPUNIT_TEST(testTokenizeNegativeInt);
  CPPUNIT_TEST(testTokenizeString);
  CPPUNIT_TEST(testTokenizeList);
  CPPUNIT_TEST_SUITE_END();
};

#endif
