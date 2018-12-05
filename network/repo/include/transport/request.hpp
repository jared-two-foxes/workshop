#ifndef NETWORK_TRANSPORT_REQUEST_HPP__
#define NETWORK_TRANSPORT_REQUEST_HPP__

#include <string>
#include <vector>

namespace network {
using std::string;

typedef std::pair<string, string > StringPair;
typedef std::vector<StringPair > ParameterList;

struct Request
{
  string uri_;
  ParameterList options_;
  ParameterList parameters_;
  string content_;
};

} // namespace oauth2

#endif // NETWORK_TRANSPORT_REQUEST_HPP__
