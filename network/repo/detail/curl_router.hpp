#ifndef NETWORK_CURLREQUESTROUTER_HPP__
#define NETWORK_CURLREQUESTROUTER_HPP__

#include <network/transport/router.hpp>

#include <curl/curl.h>
#include <string>

namespace network {

class CurlRouter : public Router
{
private:
    CURL* m_curl;

public:
    CurlRouter();
    virtual ~CurlRouter();

    void init() override;
    void destroy() override;
    util::Status perform( Request& request, Response* response ) override;

private:
    curl_slist* setupHeader( Request& request );
    std::string setupUrlWithParameters( Request& request );
    void setupBody( Request& request );

};

}

#endif // NETWORK_CURLREQUESTSTACK_HPP__
