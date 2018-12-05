
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

network::util::Status network::oauth2::requestAuth( oauth2::ClientSpec& spec, std::string scopes, network::Request* request )
{
    std::cout
        << std::endl
        << "Welcome to the Google APIs for C++ CalendarSample.\n"
        << "  You will need to authorize this program to look at your calendar.\n"
        << "  If you would like to save these credentials between runs\n"
        << "  (or restore from an earlier run) then enter a Google Email "
           "Address.\n"
        << "  Otherwise just press return.\n" << std::endl
        << "  Address: ";
    string email;
    std::getline(std::cin, email);
    if (!email.empty()) {
        network::util::Status status = ValidateUserName(email);
        if (!status.ok()) {
            return status;
        }
    }

    // I'm going to assume these lines are related to glog
    // CHECK(!scopes.empty());
    // CHECK(!client_spec_.client_id().empty()) << "client_id not set";

    request->uri_ =
        StrCat(spec.auth_uri_,
               "?client_id=", EscapeForUrl(spec.client_id_),
               "&redirect_uri=", EscapeForUrl(spec.redirect_uri_),
               "&scope=", EscapeForUrl(scopes),
               "&response_type=code");

    return StatusOk();
}


network::util::Status network::oauth2::confirmAuth( oauth2::ClientSpec& spec, std::string authorization_code, network::Request* request )
{
    request->content_ =
        StrCat("code=", EscapeForUrl(authorization_code),
               "&client_id=", EscapeForUrl(spec.client_id_),
               "&client_secret=", EscapeForUrl(spec.client_secret_),
               "&redirect_uri=", EscapeForUrl(spec.redirect_uri_),
               "&grant_type=authorization_code");

    return StatusOk();
}
