#include "TestBencode.h"
#include "Bencode.h"

#include <stdexcept>

void TestBencode::testDecodeLegalInts()
{
  CPPUNIT_ASSERT_EQUAL(0, Bencode::decodeInt("i0e"));
  CPPUNIT_ASSERT_EQUAL(1, Bencode::decodeInt("i1e"));
  CPPUNIT_ASSERT_EQUAL(10, Bencode::decodeInt("i10e"));
  CPPUNIT_ASSERT_EQUAL(43, Bencode::decodeInt("i43e"));
  CPPUNIT_ASSERT_EQUAL(123456789, Bencode::decodeInt("i123456789e"));

  CPPUNIT_ASSERT_EQUAL(-1, Bencode::decodeInt("i-1e"));
  CPPUNIT_ASSERT_EQUAL(-22, Bencode::decodeInt("i-22e"));
}


CPPUNIT_TEST_SUITE_REGISTRATION(TestBencode);
