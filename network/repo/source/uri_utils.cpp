

#include <network/transport/uri_utils.hpp>
#include <foundation/base/macros.hpp>
#include <foundation/strings/ascii_ctype.hpp>
using foundation::ascii_isgraph;
#include <foundation/strings/numbers.hpp>
#include <foundation/strings/stringpiece.hpp>

#include <string>
using std::string;
#include <vector>


inline bool EndsWith(string s, const char *x) {
  int l = strlen(x);
  if (s.size() < l) return false;
  return s.compare(s.size()-l, l, x) == 0;
}


// http://en.wikipedia.org/wiki/Percent-encoding
// Reserved ascii chars from RFC 3986
#define kMinReserved '!'
#define kMaxReserved ']'
#if ((kMaxReserved - kMinReserved) > 64)
#error "This wont work"
#endif
#define RESERVE_BIT(c) (static_cast<uint64_t>(1) << (c - kMinReserved))
static const uint64_t kReservedMask =
      RESERVE_BIT('%')
      | RESERVE_BIT('!') | RESERVE_BIT('*') | RESERVE_BIT('\'')
      | RESERVE_BIT('(') | RESERVE_BIT(')') | RESERVE_BIT(';')
      | RESERVE_BIT(':') | RESERVE_BIT('@') | RESERVE_BIT('&')
      | RESERVE_BIT('=') | RESERVE_BIT('+') | RESERVE_BIT('$')
      | RESERVE_BIT(',') | RESERVE_BIT('/') | RESERVE_BIT('?')
      | RESERVE_BIT('#') | RESERVE_BIT('[') | RESERVE_BIT(']');

static bool NeedsEscaping(char c) {
  // If not in the special range then only needs encoding if it isnt
  // graphical (i.e. binary)
  if (c < kMinReserved || c > kMaxReserved) return !ascii_isgraph(c);

  // Otherwise check the value against our mask.
  return (kReservedMask & 1LL << (c - kMinReserved)) != 0;
}

static string EscapeReservedCharacters(const string& from,
                                       bool (*needs_escaping)(char)) {
  const char *hex_digits = "0123456789ABCDEF";
  string escaped;
  const char* ptr = from.data();
  const char* end = ptr + from.size();
  for (; ptr < end; ++ptr) {
    if (needs_escaping(*ptr)) {
      escaped.push_back('%');
      escaped.push_back(hex_digits[(*ptr >> 4) & 0xf]);
      escaped.push_back(hex_digits[(*ptr) & 0xf]);
    } else {
      escaped.push_back(*ptr);
    }
  }
  return escaped;
}

string network::EscapeForUrl(const string& from) {
  return EscapeReservedCharacters(from, NeedsEscaping);
}
