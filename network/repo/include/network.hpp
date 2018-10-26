#ifndef SCHEDULE_NETWORK_HPP__
#define SCHEDULE_NETWORK_HPP__

#include <string>
#include <vector>

namespace network {

typedef std::pair<std::string, std::string > ParameterPair;
typedef std::vector<ParameterPair > ParameterList;

void init();
void quit();
bool setupHttpHeader( const ParameterList& parameters );
bool setUrlAndParameters( std::string endpoint, const ParameterList& parameters );
void setCallback( size_t (*fn)(void*, size_t, size_t, void*), void* data );
bool performOperation();

}

#endif // SCHEDULE_NETWORK_HPP__
