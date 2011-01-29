#ifndef TESTBENCODEDECODER_H
#define TESTBENCODEDECODER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestBencodeDecoder : public CppUnit::TestFixture
{
public:
  void testDecodeLegalInts();
  void testDecodeIllegalInts();
  void testDecodeLegalStrings();
  void testDecodeIllegalStrings();
  void testDecodeIncorrectlySizedStrings();

private:
  CPPUNIT_TEST_SUITE(TestBencodeDecoder);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST(testDecodeLegalStrings);
  CPPUNIT_TEST(testDecodeIllegalStrings);
  CPPUNIT_TEST(testDecodeIncorrectlySizedStrings);

  CPPUNIT_TEST_SUITE_END();
};

#endif
