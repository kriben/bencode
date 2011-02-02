#ifndef TESTDECODER_H
#define TESTDECODER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestDecoder : public CppUnit::TestFixture
{
public:
  void testDecodeLegalInts();
  void testDecodeIllegalInts();
  void testDecodeLegalStrings();
  void testDecodeIllegalStrings();
  void testDecodeIncorrectlySizedStrings();
  void testDecodeShortList();
  void testDecodeSimpleDictionary();
  void testDecodeNestedList();
private:
  CPPUNIT_TEST_SUITE(TestDecoder);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST(testDecodeLegalStrings);
  CPPUNIT_TEST(testDecodeIllegalStrings);
  CPPUNIT_TEST(testDecodeIncorrectlySizedStrings);
  CPPUNIT_TEST(testDecodeShortList);
  CPPUNIT_TEST(testDecodeSimpleDictionary);
  CPPUNIT_TEST(testDecodeNestedList);
  CPPUNIT_TEST_SUITE_END();
};

#endif
