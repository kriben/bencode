#include "Encoder.h"

#include <stdexcept>
#include <sstream>

class EncodeVisitor : public boost::static_visitor<std::string>
{
public:
  std::string operator()(int value) const
  {
    std::stringstream stream;
    stream << "i" << value << "e";
    return stream.str();
  }

  std::string operator()(const std::string& value) const
  {
    std::stringstream stream;
    stream << value.size() << ":" << value;
    return stream.str();
  }

  std::string operator()(const ValueDictionary& dict) const
  {
    std::stringstream stream;
    stream << "d";
    for (ValueDictionary::const_iterator i = dict.begin();
	 i != dict.end(); ++i) {
      stream << (*this)(i->first)
	     << boost::apply_visitor(EncodeVisitor(), i->second);
    }
    stream << "e";

    return stream.str();
  }

  std::string operator()(const ValueVector& vec) const
  {
    std::stringstream stream;
    stream << "l";
    for (ValueVector::const_iterator i = vec.begin(); i != vec.end(); ++i)
      stream << boost::apply_visitor(EncodeVisitor(), *i);
    stream << "e";

    return stream.str();
  }
};

std::string Encoder::encode(const Value& value)
{
  return boost::apply_visitor(EncodeVisitor(), value);
}
