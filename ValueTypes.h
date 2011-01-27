#ifndef VALUETYPES_H
#define VALUETYPES_H

#include <boost/variant.hpp>

#include <string>
#include <vector>
#include <map>

typedef boost::make_recursive_variant<
  int,
  std::string,
  std::vector<boost::recursive_variant_>,
  std::map<std::string, boost::recursive_variant_> 
>::type Value;

/// Some convenience typedefs
typedef std::map<std::string, Value> ValueDictionary;
typedef std::vector<Value> ValueVector;

#endif
