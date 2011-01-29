#include "TestBencodeDecoder.h"
#include "BencodeDecoder.h"

#include <stdexcept>


void TestBencodeDecoder::testDecodeLegalInts()
{
  CPPUNIT_ASSERT_EQUAL(0, boost::get<int>(BencodeDecoder::decode("i0e")));
  CPPUNIT_ASSERT_EQUAL(1, boost::get<int>(BencodeDecoder::decode("i1e")));
  CPPUNIT_ASSERT_EQUAL(10, boost::get<int>(BencodeDecoder::decode("i10e")));
  CPPUNIT_ASSERT_EQUAL(43, boost::get<int>(BencodeDecoder::decode("i43e")));
  CPPUNIT_ASSERT_EQUAL(123456789,
		       boost::get<int>(BencodeDecoder::decode("i123456789e")));
  CPPUNIT_ASSERT_EQUAL(-1, boost::get<int>(BencodeDecoder::decode("i-1e")));
  CPPUNIT_ASSERT_EQUAL(-22, boost::get<int>(BencodeDecoder::decode("i-22e")));
}

void TestBencodeDecoder::testDecodeIllegalInts()
{
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("ie"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("    "), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("i0f"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("i-1-2e"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("i-0e"), std::invalid_argument);
}


CPPUNIT_TEST_SUITE_REGISTRATION(TestBencodeDecoder);
