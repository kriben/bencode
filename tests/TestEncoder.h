#ifndef TESTENCODER_H
#define TESTENCODER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestEncoder : public CppUnit::TestFixture
{
public:
  void testEncodeInts();
  void testEncodeStrings();
  void testEncodeVector();
  void testEncodeDictionary();
  void testEncodeNestedDictionary();
private:
  CPPUNIT_TEST_SUITE(TestEncoder);
  CPPUNIT_TEST(testEncodeInts);
  CPPUNIT_TEST(testEncodeStrings);
  CPPUNIT_TEST(testEncodeVector);
  CPPUNIT_TEST(testEncodeDictionary);
  CPPUNIT_TEST(testEncodeNestedDictionary);
  CPPUNIT_TEST_SUITE_END();
};

#endif
