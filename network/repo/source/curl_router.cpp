
#include <network/curl_router.hpp>

#include <network/transport/request.hpp>
#include <network/transport/response.hpp>

using namespace network;

size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
{
    std::size_t nb = size * nmemb;
    std::string buffer( (char*)contents, nb );
    ((Response*)userp)->buffer_.append( buffer );
    return nb;
}

CurlRouter::CurlRouter()
{}

CurlRouter::~CurlRouter()
{}

void CurlRouter::init()
{
    m_curl = curl_easy_init();
}

void CurlRouter::destroy()
{
    if ( m_curl )
    {
        curl_easy_cleanup( m_curl );
        m_curl = nullptr;
    }
}

// Should this be a pair, obj & error?
util::Status CurlRouter::perform( Request& request, Response* response )
{
    CURLcode res;

    struct curl_slist* chunk = setupHeader( request );
    res = curl_easy_setopt( m_curl, CURLOPT_HTTPHEADER, chunk );
    std::string url = setupUrlWithParameters( request );
    res = curl_easy_setopt( m_curl, CURLOPT_URL, url.c_str() );
    res = curl_easy_setopt( m_curl, CURLOPT_WRITEDATA, response );
    res = curl_easy_setopt( m_curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    res = curl_easy_perform( m_curl );

    if ( chunk )
    {
        curl_slist_free_all( chunk );
        chunk = nullptr;
    }

    if (res != CURLE_OK)
    {
        return network::util::StatusUnknown("Failed to perform operation");
    }

    return network::util::StatusOk();
}

curl_slist* CurlRouter::setupHeader( Request& request )
{
    curl_slist* chunk = nullptr;

    ParameterList options = request.options_;
    for ( auto& pair : options )
    {
        std::string option = pair.first + ": " + pair.second;
        chunk = curl_slist_append( chunk, option.c_str() );
    }

    //assert( res == CURLE_OK );
    return chunk;
}

std::string CurlRouter::setupUrlWithParameters( Request& request )
{
    std::string url = request.uri_;

    int32_t i = 0;
    ParameterList parameters = request.parameters_;
    for ( auto& pair : parameters )
    {
        url += ( i == 0 ? "?" : "&" );
        url += pair.first;
        if( pair.second.length() > 0 )
        {
            url += std::string("=") + pair.second;
        }
        i++;
    }

    return url;
}
