#ifndef TESTENCODER_H
#define TESTENCODER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestEncoder : public CppUnit::TestFixture
{
public:
  void testEncodeInts();
private:
  CPPUNIT_TEST_SUITE(TestEncoder);
  CPPUNIT_TEST(testEncodeInts);
  CPPUNIT_TEST_SUITE_END();
};

#endif
