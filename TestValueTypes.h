#ifndef TESTVALUETYPES_H
#define TESTVALUETYPES_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestValueTypes : public CppUnit::TestFixture
{
public:
  void testInteger();

  void testString();

  void testVector();

  void testRecursiveVector();

private:
  CPPUNIT_TEST_SUITE(TestValueTypes);
  CPPUNIT_TEST(testInteger);
  CPPUNIT_TEST(testString);
  CPPUNIT_TEST(testVector);
  CPPUNIT_TEST(testRecursiveVector);
  CPPUNIT_TEST_SUITE_END();
};

#endif
