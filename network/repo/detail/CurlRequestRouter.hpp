#ifndef NETWORK_CURLREQUESTROUTER_HPP__
#define NETWORK_CURLREQUESTROUTER_HPP__

#include <network/RequestRouter.hpp>
#include <curl/curl.h>
#include <string>

namespace network {

class CurlRequestRouter : public RequestRouter
{
private:
    CURL* m_curl;

public:
    CurlRequestRouter();
    virtual ~CurlRequestRouter();

    void init() override;
    void destroy() override;
    Response* perform( Request* request ) override;

private:
    curl_slist* setupHeader( Request* request );
    std::string setupUrlWithParameters( Request* request );
    //void setupBody( Request* request );

};

}

#endif // NETWORK_CURLREQUESTSTACK_HPP__
