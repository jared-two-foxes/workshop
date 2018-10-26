
#include <network/CurlRequestRouter.hpp>
#include <network/Request.hpp>
#include <network/Response.hpp>

using namespace network;


size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
{
    std::size_t nb = size * nmemb;
    std::string buffer( (char*)contents, nb );
    ((Response*)userp)->Write( buffer );
    return nb;
}

CurlRequestRouter::CurlRequestRouter()
{}

CurlRequestRouter::~CurlRequestRouter()
{}

void CurlRequestRouter::init()
{
    m_curl = curl_easy_init();
}

void CurlRequestRouter::destroy()
{
    if ( m_curl )
    {
        curl_easy_cleanup( m_curl );
        m_curl = nullptr;
    }
}

// Should this be a pair, obj & error?
Response* CurlRequestRouter::perform( Request* request )
{
    CURLcode res;

    struct curl_slist* chunk = setupHeader( request );
    res = curl_easy_setopt( m_curl, CURLOPT_HTTPHEADER, chunk );

    std::string url = setupUrlWithParameters( request );
    res = curl_easy_setopt( m_curl, CURLOPT_URL, url.c_str() );

    Response* response = new Response();
    res = curl_easy_setopt( m_curl, CURLOPT_WRITEDATA, response );
    res = curl_easy_setopt( m_curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    res = curl_easy_perform( m_curl );

    if ( chunk )
    {
        curl_slist_free_all( chunk );
        chunk = nullptr;
    }

    //return (res == CURLE_OK);
    return response;
}

curl_slist* CurlRequestRouter::setupHeader( Request* request )
{
    curl_slist* chunk = nullptr;

    ParameterList options = request->getOptions();
    for ( auto& pair : options )
    {
        std::string option = pair.first + ": " + pair.second;
        chunk = curl_slist_append( chunk, option.c_str() );
    }

    //return ( res == CURLE_OK );
    return chunk;
}

std::string CurlRequestRouter::setupUrlWithParameters( Request* request )
{
    std::string url = request->getUrl();

    int32_t i = 0;
    ParameterList parameters = request->getParameters();
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
