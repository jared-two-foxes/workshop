
#include <network/Request.hpp>

using namespace network;

Request::Request( std::string endpoint, ParameterList& options ) :
    m_endpoint(endpoint),
    m_options(options)
{}

void Request::setParameters( ParameterList parameters )
{
    m_parameters = parameters;
}

std::string Request::getUrl()
{
    return m_endpoint;
}

ParameterList Request::getOptions()
{
    return m_options;
}

ParameterList Request::getParameters()
{
    return m_parameters;
}
