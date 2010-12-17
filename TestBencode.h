#ifndef TESTBENCODE_H
#define TESTBENCODE_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestBencode : public CppUnit::TestFixture
{
public:
  void testDecodeLegalInts();
  void testDecodeIllegalInts();
  void testDecodeLegalStrings();
  void testDecodeIllegalStrings();
private:
  CPPUNIT_TEST_SUITE(TestBencode);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST(testDecodeLegalStrings);
  CPPUNIT_TEST(testDecodeIllegalStrings);
  CPPUNIT_TEST_SUITE_END();
};

#endif
