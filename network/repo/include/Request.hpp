#ifndef NETWORK_NETWORKREQUEST_HPP__
#define NETWORK_NETWORKREQUEST_HPP__

#include <foundation/foundation.hpp>

#include <string>
#include <vector>

namespace network {

typedef std::pair<std::string, std::string > StringPair;
typedef std::vector<StringPair > ParameterList;

class Request
{
private:
    std::string m_endpoint;
    ParameterList m_options;
    ParameterList m_parameters;

public:
    Request( std::string endpoint, ParameterList& options );

    void setParameters( ParameterList parameters );

    std::string getUrl();
    ParameterList getOptions();
    ParameterList getParameters();

};

}

#endif //
