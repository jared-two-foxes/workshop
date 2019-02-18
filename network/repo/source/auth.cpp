
#include <network/auth/authenticate.hpp>

#include <network/status.hpp>
#include <network/transport/uri_utils.hpp>

#include <foundation/strings/strcat.hpp>

#include <string>
using std::string;
#include <iostream>

using namespace foundation;

using network::util::StatusCanceled;
using network::util::StatusInvalidArgument;
using network::util::StatusOk;

network::util::Status ValidateUserName(const string& name)
{
  if (name.find("/") != string::npos)
  {
    return StatusInvalidArgument("UserNames cannot contain '/'");
  }
  else if (name == "." || name == "..")
  {
    return StatusInvalidArgument(
        StrCat("'", name, "' is not a valid UserName"));
  }
  return StatusOk();
}

string network::oauth2::requestAuth( string auth, oauth2::ClientInfo& spec, string redirect, string scopes )
{
  // I'm going to assume these lines are related to glog
  // CHECK(!scopes.empty());
  // CHECK(!client_spec_.client_id().empty()) << "client_id not set";

  return
    StrCat(auth,
      "?client_id=", EscapeForUrl(spec.client_id_),
      "&redirect_uri=", EscapeForUrl(redirect),
      "&scope=", EscapeForUrl(scopes),
      "&response_type=code");
}


string network::oauth2::confirmAuth( oauth2::ClientInfo& spec, string redirect, string authorization_code )
{
  return
    StrCat("code=", authorization_code,
      "&client_id=", EscapeForUrl(spec.client_id_),
      "&client_secret=", EscapeForUrl(spec.client_secret_),
      "&redirect_uri=", EscapeForUrl(redirect),
      "&grant_type=authorization_code");
}
