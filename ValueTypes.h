#ifndef BENCODE_VALUETYPES_H
#define BENCODE_VALUETYPES_H

#include <boost/variant.hpp>

#include <string>
#include <vector>
#include <map>

namespace bencode {

  typedef boost::make_recursive_variant<
    int,
    std::string,
    std::vector<boost::recursive_variant_>,
    std::map<std::string, boost::recursive_variant_> >::type Value;

  typedef std::map<std::string, Value> ValueDictionary;
  typedef std::vector<Value> ValueVector;

};

#endif
