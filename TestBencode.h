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

private:
  CPPUNIT_TEST_SUITE(TestBencode);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST(testDecodeLegalStrings);
  CPPUNIT_TEST(testDecodeIllegalStrings);
  CPPUNIT_TEST(testDecodeIncorrectlySizedStrings);
  CPPUNIT_TEST_SUITE_END();
};

#endif
