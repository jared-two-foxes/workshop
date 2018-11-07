#ifndef NETWORK_URLTOOLS_HPP__
#define NETWORK_URLTOOLS_HPP__

#include <string>
using std::string;

namespace network {

/*
 * Escape a string so that it is valid in a URL.
 * @ingroup PlatformLayerUri
 *
 * @param[in] s The string to escape.
 * @return the escaped string.
 */
string EscapeForUrl(const string& s);

}

#endif // NETWORK_URLTOOLS_HPP__
