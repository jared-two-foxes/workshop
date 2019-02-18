#ifndef SCHEDULE_AUTHENTICATE_HPP_
#define SCHEDULE_AUTHENTICATE_HPP_

#include <network/status.hpp>
#include <network/transport/request.hpp>

#include <string>

namespace network {
using std::string;

namespace oauth2 {

/*
 * Specifies an OAuth 2.0 Credential.
 */
struct Credential
{
  string access_token_;
  string refresh_token_;
  int64_t expiration_timestamp_secs_;
  // string email_;
  // bool email_verified_;
};

/*
 * A data object containing specifying the client information to present to
 * the OAuth 2.0 server.
 */
struct ClientInfo
{
  string client_id_;
  string client_secret_;
};

string requestAuth( string auth, oauth2::ClientInfo& spec, std::string redirect, string scopes );

string confirmAuth( oauth2::ClientInfo& spec, string redirect, string authorization_code );

}  // namespace oauth2

}  // namespace network

#endif // SCHEDULE_AUTHENTICATE_HPP_
