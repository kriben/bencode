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


void TestBencodeDecoder::testDecodeLegalStrings()
{
  CPPUNIT_ASSERT_EQUAL(std::string("spam"),
		       boost::get<std::string>(BencodeDecoder::decode("4:spam")));
  CPPUNIT_ASSERT_EQUAL(std::string("yes"),
   		       boost::get<std::string>(BencodeDecoder::decode("3:yes")));
  CPPUNIT_ASSERT_EQUAL(std::string("Kristian Bendiksen"),
   		       boost::get<std::string>(BencodeDecoder::decode("18:Kristian Bendiksen")));
  CPPUNIT_ASSERT_EQUAL(std::string(""),
		       boost::get<std::string>(BencodeDecoder::decode("0:")));
}

void TestBencodeDecoder::testDecodeIllegalStrings()
{
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("spam"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("-2:no"), std::invalid_argument);
}

void TestBencodeDecoder::testDecodeIncorrectlySizedStrings()
{
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("3:no"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(BencodeDecoder::decode("2:yes"), std::invalid_argument);
}


void TestBencodeDecoder::testDecodeShortList()
{
  ValueVector vec =
    boost::get<ValueVector>(BencodeDecoder::decode("l4:spam4:eggse"));

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), vec.size());
  CPPUNIT_ASSERT_EQUAL(std::string("spam"), boost::get<std::string>(vec[0]));
  CPPUNIT_ASSERT_EQUAL(std::string("eggs"), boost::get<std::string>(vec[1]));
}


void TestBencodeDecoder::testDecodeSimpleDictionary()
{
  ValueDictionary dict =
    boost::get<ValueDictionary>(
      BencodeDecoder::decode("d3:cow3:moo4:spam4:eggse"));

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), dict.size());
  CPPUNIT_ASSERT_EQUAL(std::string("moo"),
		       boost::get<std::string>(dict["cow"]));

  CPPUNIT_ASSERT_EQUAL(std::string("eggs"),
		       boost::get<std::string>(dict["spam"]));
}

void TestBencodeDecoder::testDecodeNestedList()
{
  ValueVector firstVector =
    boost::get<ValueVector>(
      BencodeDecoder::decode("lll5:first6:seconde7:missingee"));
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), firstVector.size());

  ValueVector secondVector = boost::get<ValueVector>(firstVector[0]);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), secondVector.size());

  CPPUNIT_ASSERT_EQUAL(std::string("missing"),
		       boost::get<std::string>(secondVector[1]));

  ValueVector thirdVector = boost::get<ValueVector>(secondVector[0]);
  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), thirdVector.size());

  CPPUNIT_ASSERT_EQUAL(std::string("first"),
		       boost::get<std::string>(thirdVector[0]));

  CPPUNIT_ASSERT_EQUAL(std::string("second"),
		       boost::get<std::string>(thirdVector[1]));
}


CPPUNIT_TEST_SUITE_REGISTRATION(TestBencodeDecoder);
