
#include <network/curl_router.hpp>

#include <network/transport/request.hpp>
#include <network/transport/response.hpp>

#include <iostream>

using namespace network;

size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
{
    std::size_t nb = size * nmemb;
    std::string buffer( (char*)contents, nb );
    ((Response*)userp)->body_.append( buffer );
    return nb;
}

curl_slist* setupHeader( Request const & request )
{
    curl_slist* chunk = nullptr;

    ParameterList options = request.options_;
    for ( auto pair : options )
    {
        std::string option = pair.first + ": " + pair.second;
        chunk = curl_slist_append( chunk, option.c_str() );
    }

    return chunk;
}


CURLoption selectRequestMethod( Request const & request ) 
{
    switch ( request.method_ )
    {
    case HttpMethod::GET:
        return CURLOPT_HTTPGET;
    case HttpMethod::POST:
        return CURLOPT_POST;
    case HttpMethod::PUT:
        return CURLOPT_PUT;
    // case HttpMethod::HEAD:
    //     return CURLOPT_PUT;
    default:
        break;
    }

    return CURLOPT_HTTPGET;
}

CurlRouter::CurlRouter()
{}

CurlRouter::~CurlRouter()
{}

void 
CurlRouter::init()
{
    m_curl = curl_easy_init();
}

void 
CurlRouter::destroy()
{
    if ( m_curl )
    {
        curl_easy_cleanup( m_curl );
        m_curl = nullptr;
    }
}

// Should this be a pair, obj & error?
util::Status 
CurlRouter::perform( Request const & request, Response* response )
{
    CURLcode res;

    CURLoption option = selectRequestMethod( request );
    res = curl_easy_setopt( m_curl, option, 1L );

    struct curl_slist* chunk = setupHeader( request );
    res = curl_easy_setopt( m_curl, CURLOPT_HTTPHEADER, chunk ); 

    if (!request.content_.empty()) {
        //@todo: Maybe we should assert here that post is selected?
        std::cout << request.content_ << std::endl;
        res = curl_easy_setopt( m_curl, CURLOPT_POSTFIELDS, 
            request.content_.c_str() );
    }

    res = curl_easy_setopt( 
        m_curl, CURLOPT_WRITEDATA, response );
    res = curl_easy_setopt( 
        m_curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    res = curl_easy_setopt( m_curl, CURLOPT_URL, request.uri_.c_str() );
    
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

