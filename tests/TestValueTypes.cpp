#include "TestValueTypes.h"
#include "ValueTypes.h"

using namespace bencode;

void TestValueTypes::testInteger()
{
  Value three = 3;
  Value four = 4;

  CPPUNIT_ASSERT_EQUAL(7, boost::get<int>(three) + boost::get<int>(four));
}

void TestValueTypes::testString()
{
  Value myName = "Kristian";
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8),
		       boost::get<std::string>(myName).size());
}

void TestValueTypes::testVector()
{
  ValueVector vec;
  vec.push_back("Kristian");
  vec.push_back(1979);

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), vec.size());
  CPPUNIT_ASSERT_THROW(boost::get<int>(vec[0]), boost::bad_get);
}

void TestValueTypes::testRecursiveVector()
{
  ValueVector innerVec;
  innerVec.push_back("Test");
  innerVec.push_back("Driven");
  innerVec.push_back("Design");
  innerVec.push_back(2011);

  ValueVector outerVec;
  outerVec.push_back(innerVec);

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), innerVec.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), outerVec.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), boost::get<ValueVector>(outerVec[0]).size());
}


CPPUNIT_TEST_SUITE_REGISTRATION(TestValueTypes);
