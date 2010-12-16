#include "TestBencode.h"
#include "Bencode.h"

void TestBencode::testDecodeLegalInts()
{
  CPPUNIT_ASSERT_EQUAL(0, Bencode::decodeInt("i0e"));
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestBencode);
