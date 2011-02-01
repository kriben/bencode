#ifndef PRETTYPRINTER_H
#define PRETTYPRINTER_H


#include "ValueTypes.h"

#include <boost/variant/apply_visitor.hpp>


class PrettyPrinter : public boost::static_visitor<>
{
public:
  PrettyPrinter(int indentation = 0);

  int getIndentation() const;

  void operator()(int t) const;

  void operator()(const std::string& t) const;

  void operator()(const ValueDictionary& t) const;

  void operator()(const ValueVector& t) const;

private:
  std::string getSpace() const;

  bool isAscii(int c) const;

  bool isAscii(const std::string& value) const;

private:
  int indentation_;
};

#endif
