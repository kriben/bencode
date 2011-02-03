#include "TestEncoder.h"
#include "Encoder.h"
#include "Decoder.h"

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


void TestEncoder::testEncodeVector()
{
  ValueVector vec;
  vec.push_back(Value("Red"));
  vec.push_back(Value("Green"));
  vec.push_back(Value(12));
  vec.push_back(Value(-13));

  std::string expected = "l3:Red5:Greeni12ei-13ee";
  CPPUNIT_ASSERT_EQUAL(expected, Encoder::encode(vec));
}

void TestEncoder::testEncodeDictionary()
{
  ValueDictionary dict;
  dict["Hamar"] = Value(2319);
  dict["Trondheim"] = Value(7041);

  std::string expected = "d5:Hamari2319e9:Trondheimi7041ee";
  CPPUNIT_ASSERT_EQUAL(expected, Encoder::encode(dict));
}


void TestEncoder::testEncodeNestedDictionary()
{
  ValueDictionary spursPlayers;
  spursPlayers["11"] = Value("Van der Vaart");
  spursPlayers["26"] = Value("King");

  ValueDictionary barcaPlayers;
  barcaPlayers["10"] = Value("Messi");
  barcaPlayers["6"] = Value("Xavi");

  ValueDictionary teams;
  teams["Tottenham"] = spursPlayers;
  teams["Barcelona"] = barcaPlayers;

  std::string expected = "d9:Barcelonad2:105:Messi1:64:Xavie"
    "9:Tottenhamd2:1113:Van der Vaart2:264:Kingee";

  CPPUNIT_ASSERT_EQUAL(expected, Encoder::encode(teams));
}

void TestEncoder::testIntegerRoundtrip()
{
  Value input = 3;
  Value output = Decoder::decode(Encoder::encode(input));
  CPPUNIT_ASSERT_EQUAL(boost::get<int>(input), boost::get<int>(output));
}

void TestEncoder::testStringRoundtrip()
{
  Value input = "Fram og tilbake er like langt";
  Value output = Decoder::decode(Encoder::encode(input));
  CPPUNIT_ASSERT_EQUAL(boost::get<std::string>(input),
		       boost::get<std::string>(output));
}



CPPUNIT_TEST_SUITE_REGISTRATION(TestEncoder);
