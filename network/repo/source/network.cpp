
#include <network/network.hpp>

#include <curl/curl.h>

struct curl_slist* chunk = nullptr;
CURL* curl = nullptr;


namespace network {

void init()
{
    curl = curl_easy_init();
}

void quit()
{
    if (chunk)
    {
        curl_slist_free_all( chunk );
        chunk = nullptr;
    }

    if (curl)
    {
        curl_easy_cleanup( curl );
        curl = nullptr;
    }
}


bool setupHttpHeader( const ParameterList& parameters )
{
    // Clear the current chunk?
    curl_slist_free_all( chunk );
    chunk = nullptr;

    for ( auto& pair : parameters )
    {
        std::string option = pair.first + ": " + pair.second;
        chunk = curl_slist_append( chunk, option.c_str() );
    }

    CURLcode res = curl_easy_setopt( curl, CURLOPT_HTTPHEADER, chunk );

    return ( res == CURLE_OK );
}

bool setUrlAndParameters( std::string endpoint, const ParameterList& parameters )
{
    std::string request = endpoint;

    int32_t i = 0;
    for ( auto& pair : parameters )
    {
        request += ( i == 0 ? "?" : "&" );
        request += pair.first;
        if( pair.second.length() > 0 )
        {
            request += std::string("=") + pair.second;
        }
        i++;
    }

    curl_easy_setopt( curl, CURLOPT_URL, request.c_str() );

    return true;
}

void setCallback( size_t (*fn)(void*, size_t, size_t, void*), void* data )
{
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, fn );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, data );
}

bool performOperation()
{
    CURLcode res = curl_easy_perform( curl );
    return (res == CURLE_OK);
}

}
