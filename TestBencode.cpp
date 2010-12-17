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

void TestBencode::testDecodeIllegalInts()
{
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("ie"), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt(""), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("    "), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i0f"), std::invalid_argument);  
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i-1-2e"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeInt("i-0e"), std::invalid_argument);
}

void TestBencode::testDecodeLegalStrings()
{
  CPPUNIT_ASSERT_EQUAL(std::string("spam"), Bencode::decodeString("4:spam"));
  CPPUNIT_ASSERT_EQUAL(std::string("yes"), Bencode::decodeString("3:yes"));
  CPPUNIT_ASSERT_EQUAL(std::string("Kristian Bendiksen"),
		       Bencode::decodeString("18:Kristian Bendiksen"));
}

void TestBencode::testDecodeIllegalStrings()
{
  CPPUNIT_ASSERT_THROW(Bencode::decodeString(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("spam"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Bencode::decodeString("-2:no"), std::invalid_argument);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestBencode);
