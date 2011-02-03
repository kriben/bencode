#include "ValueTypes.h"
#include "PrettyPrinter.h"

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant.hpp>

#include <iostream>

using namespace bencode;

PrettyPrinter::PrettyPrinter(int indentation)
  : indentation_(indentation)
{
}

int PrettyPrinter::getIndentation() const
{
  return indentation_;
}

std::string PrettyPrinter::getSpace() const
{
  return std::string(getIndentation() * 2, ' ');
}

bool PrettyPrinter::isAscii(int c) const
{
  return (c >= 9 && c <= 13) || (c >= 32 && c <= 126);
}

bool PrettyPrinter::isAscii(const std::string& value) const
{
  for (unsigned int i = 0; i < value.size(); i++)
    if (!isAscii(static_cast<int>(value[i])))
      return false;

  return true;
}

void PrettyPrinter::operator()(int t) const
{
  std::cout << t << std::endl;
}

void PrettyPrinter::operator()(const std::string& t) const
{
  if (!isAscii(t))
    std::cout << "BINARY DATA (length: " << t.size() << ")" << std::endl;
  else {
    const int MAX_STRING_LENGTH = 100;
    std::cout << t.substr(0, MAX_STRING_LENGTH) << std::endl;
  }
}

void PrettyPrinter::operator()(const ValueDictionary& t) const
{
  std::cout << std::endl;
  for (ValueDictionary::const_iterator i = t.begin(); i != t.end(); ++i) {
    std::cout << getSpace() << "{" << i->first << "}: ";
    boost::apply_visitor(PrettyPrinter(getIndentation() + 1), i->second);
  }
}

void PrettyPrinter::operator()(const ValueVector& t) const
{
  std::cout << std::endl;
  for (unsigned int i = 0; i != t.size(); ++i) {
    std::cout << getSpace() << "[" << i << "]: ";
    boost::apply_visitor(PrettyPrinter(getIndentation() + 1), t[i]);
  }
}
