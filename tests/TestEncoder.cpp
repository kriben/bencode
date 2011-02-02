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


CPPUNIT_TEST_SUITE_REGISTRATION(TestEncoder);
