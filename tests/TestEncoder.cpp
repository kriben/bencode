#include "TestEncoder.h"
#include "Encoder.h"

#include <stdexcept>


void TestEncoder::testEncodeInts()
{
  Value three = 3;
  CPPUNIT_ASSERT_EQUAL(std::string("i3e"), Encoder::encode(three));

  Value zero = 0;
  CPPUNIT_ASSERT_EQUAL(std::string("i0e"), Encoder::encode(zero));
}

void TestEncoder::testEncodeStrings()
{
  Value name = "Kristian";
  CPPUNIT_ASSERT_EQUAL(std::string("8:Kristian"), Encoder::encode(name));

  Value emptyString = "";
  CPPUNIT_ASSERT_EQUAL(std::string("0:"), Encoder::encode(emptyString));
}


CPPUNIT_TEST_SUITE_REGISTRATION(TestEncoder);
