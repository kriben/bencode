#include "TestDecoder.h"
#include "Decoder.h"

#include <stdexcept>

using namespace bencode;

void TestDecoder::testDecodeLegalInts()
{
  CPPUNIT_ASSERT_EQUAL(0, boost::get<int>(Decoder::decode("i0e")));
  CPPUNIT_ASSERT_EQUAL(1, boost::get<int>(Decoder::decode("i1e")));
  CPPUNIT_ASSERT_EQUAL(10, boost::get<int>(Decoder::decode("i10e")));
  CPPUNIT_ASSERT_EQUAL(43, boost::get<int>(Decoder::decode("i43e")));
  CPPUNIT_ASSERT_EQUAL(123456789,
		       boost::get<int>(Decoder::decode("i123456789e")));
  CPPUNIT_ASSERT_EQUAL(-1, boost::get<int>(Decoder::decode("i-1e")));
  CPPUNIT_ASSERT_EQUAL(-22, boost::get<int>(Decoder::decode("i-22e")));
}

void TestDecoder::testDecodeIllegalInts()
{
  CPPUNIT_ASSERT_THROW(Decoder::decode("ie"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("    "), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("i0f"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("i-1-2e"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("i-0e"), std::invalid_argument);
}


void TestDecoder::testDecodeLegalStrings()
{
  CPPUNIT_ASSERT_EQUAL(std::string("spam"),
		       boost::get<std::string>(Decoder::decode("4:spam")));
  CPPUNIT_ASSERT_EQUAL(std::string("yes"),
   		       boost::get<std::string>(Decoder::decode("3:yes")));
  CPPUNIT_ASSERT_EQUAL(std::string("Kristian Bendiksen"),
   		       boost::get<std::string>(Decoder::decode("18:Kristian Bendiksen")));
  CPPUNIT_ASSERT_EQUAL(std::string(""),
		       boost::get<std::string>(Decoder::decode("0:")));
}

void TestDecoder::testDecodeIllegalStrings()
{
  CPPUNIT_ASSERT_THROW(Decoder::decode(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("spam"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("-2:no"), std::invalid_argument);
}

void TestDecoder::testDecodeIncorrectlySizedStrings()
{
  CPPUNIT_ASSERT_THROW(Decoder::decode("3:no"), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(Decoder::decode("2:yes"), std::invalid_argument);
}


void TestDecoder::testDecodeShortList()
{
  ValueVector vec =
    boost::get<ValueVector>(Decoder::decode("l4:spam4:eggse"));

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), vec.size());
  CPPUNIT_ASSERT_EQUAL(std::string("spam"), boost::get<std::string>(vec[0]));
  CPPUNIT_ASSERT_EQUAL(std::string("eggs"), boost::get<std::string>(vec[1]));
}


void TestDecoder::testDecodeSimpleDictionary()
{
  ValueDictionary dict =
    boost::get<ValueDictionary>(
      Decoder::decode("d3:cow3:moo4:spam4:eggse"));

  CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), dict.size());
  CPPUNIT_ASSERT_EQUAL(std::string("moo"),
		       boost::get<std::string>(dict["cow"]));

  CPPUNIT_ASSERT_EQUAL(std::string("eggs"),
		       boost::get<std::string>(dict["spam"]));
}

void TestDecoder::testDecodeNestedList()
{
  ValueVector firstVector =
    boost::get<ValueVector>(
      Decoder::decode("lll5:first6:seconde7:missingee"));
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


CPPUNIT_TEST_SUITE_REGISTRATION(TestDecoder);
