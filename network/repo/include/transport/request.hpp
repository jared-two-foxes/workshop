#ifndef NETWORK_TRANSPORT_REQUEST_HPP__
#define NETWORK_TRANSPORT_REQUEST_HPP__

#include <string>
#include <vector>

namespace network {

using std::string;

typedef std::pair<string, string > StringPair;
typedef std::vector<StringPair > ParameterList;

enum class HttpMethod {
  GET,
  POST,
  PUT,
  HEAD,
  DELETE, 
  PATCH,
  OPTIONS
};


struct Request
{
  HttpMethod method_;
  string uri_;
  ParameterList options_;
  string content_;
};

} // namespace oauth2

#endif // NETWORK_TRANSPORT_REQUEST_HPP__
