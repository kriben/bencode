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

  std::string operator()(const ValueDictionary& t) const
  {
    return "";
  }

  std::string operator()(const ValueVector& t) const
  {
    return "";
  }


};

std::string Encoder::encode(const Value& value)
{
  return boost::apply_visitor(EncodeVisitor(), value);
}
