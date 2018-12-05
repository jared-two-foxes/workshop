#ifndef NETWORK_API_STATUS_H_
#define NETWORK_API_STATUS_H_

#include <string>

namespace network {
using std::string;

namespace util {
namespace error {

/*
 * <table><tr><th>Code<th>Indented Purpose
 * <tr><td>OK
 *     <td>Everything is fine; no error.
 * <tr><td>CANCELLED
 *     <td>The operation has been cancelled.
 * <tr><td>UNKNOWN
 *     <td>The cause of error is unknown.
 * <tr><td>INVALID_ARGUMENT
 *     <td>The operation received an invalid argument.
 * <tr><td>DEADLINE_EXCEEDED
 *     <td>The operation terminated early due to a deadline.
 * <tr><td>NOT_FOUND
 *     <td>The requested resource or data element was missing.
 * <tr><td>ALREADY_EXISTS
 *     <td>The resource or data element already exists.
 * <tr><td>PERMISSION_DENIED
 *     <td>The caller has insufficient permission to perform the operation.
 * <tr><td>RESOURCE_EXHAUSTED
 *     <td>Not enough resources (usually memory, disk etc) to perform the
 *         operation.
 * <tr><td>FAILED_PRECONDITION
 *     <td>The caller did not meet the operation's requirements.
 * <tr><td>ABORTED
 *     <td>The operation aborted prematurely for some reason.
 * <tr><td>OUT_OF_RANGE
 *     <td>The requested resource or data element is not valid. Usually this
 *         refers to some index or key.
 * <tr><td>UNIMPLEMENTED
 *     <td>The requestd operation is not fully implemented.
 * <tr><td>INTERNAL
 *     <td>An error in the implementation was detected.
 * <tr><td>UNAVAILABLE
 *     <td>Some resource or data is not available to perform the operation now.
 * <tr><td>DATA_LOSS
 *     <td>The operation could not access all the data, or lost some along
 *         the way.
 * </table>
 */
enum Code {
  OK = 0,
  CANCELLED = 1,
  UNKNOWN = 2,
  INVALID_ARGUMENT = 3,
  DEADLINE_EXCEEDED = 4,
  NOT_FOUND = 5,
  ALREADY_EXISTS = 6,
  PERMISSION_DENIED = 7,
  RESOURCE_EXHAUSTED = 8,
  FAILED_PRECONDITION = 9,
  ABORTED = 10,
  OUT_OF_RANGE = 11,
  UNIMPLEMENTED = 12,
  INTERNAL = 13,
  UNAVAILABLE = 14,
  DATA_LOSS = 15,
};

}  // namespace error

/*
 * Denotes whether a call or object is error free, and explains why if not.
 *
 * Status objects are used through the Google APIs Client Library for C++
 * to return and propagate errors rather than using C++ exceptions. If the
 * status is not ok() then the code() and error_message() will indicate why.
 */
struct Status
{
public:
  network::util::error::Code code_;
  std::string msg_;

public:
  /*
   * Constructs a default OK status.
   */
  Status() : code_(network::util::error::OK) {}

  /*
   * Constructs a status with the given code and message.
   * @param[in] code The status code for the instance.
   * @param[in] msg If the code is other than OK then this should not be empty.
   */
  Status(network::util::error::Code code, const std::string& msg)
      : code_(code), msg_(msg) {}

  /*
   * Copy constructor.
   */
  Status(const Status& status) : code_(status.code_), msg_(status.msg_) {}

  /*
   * Standard destructor.
   */
  ~Status() {}

  /*
   * Assignment operator.
   */
  Status& operator =(const Status& status) {
    code_ = status.code_;
    msg_ = status.msg_;
    return *this;
  }

  /*
   * Equality operator.
   */
  bool operator ==(const Status& status) const {
    return code_ == status.code_ && msg_ == status.msg_;
  }

  /*
   * Determine if the status is ok().
   * @return true if the error code is OK, false otherwise.
   */
  bool ok() const { return code_ == network::util::error::OK; }

  /*
   * Get explanation bound at construction.
   */
  const std::string& error_message() const  { return msg_; }

  /*
   * Get error_code bound at construction.
   */
  network::util::error::Code error_code() const { return code_; }

  /*
   * Convert the status to a detailed string.
   *
   * If displaying the error to a user than error_message might be preferred
   * since it has less technical jargon.
   *
   * @see error_message()
   */
  std::string ToString() const;

};

/*
 * Shorthand notation for creating a status from a standard util::error enum
 * The symbol parameter is the symbolic enum name with the util::error
 * namespace stripped from it.
 */
#define STATUS_FROM_ENUM(symbol, msg) \
  Status(util::error::symbol, msg)

/*
 * Creates a standard OK status.
 */
inline Status  StatusOk() { return Status(); }

/*
 * Creates a standard ABORTED status.
 */
inline Status StatusAborted(const string& msg) {
  return STATUS_FROM_ENUM(ABORTED, msg);
}

/*
 * Creates a standard CANCELLED status.
 */
inline Status StatusCanceled(const string& msg) {
  return STATUS_FROM_ENUM(CANCELLED, msg);
}

/*
 * Creates a standard DATA_LOSS status.
 */
inline Status StatusDataLoss(const string& msg) {
  return STATUS_FROM_ENUM(DATA_LOSS, msg);
}

/*
 * Creates a standard DEADLINE_EXCEEDED status.
 */
inline Status StatusDeadlineExceeded(const string& msg) {
  return STATUS_FROM_ENUM(DEADLINE_EXCEEDED, msg);
}

/*
 * Creates a standard INTERNAL status.
 */
inline Status StatusInternalError(const string& msg) {
  return STATUS_FROM_ENUM(INTERNAL, msg);
}

/*
 * Creates a standard INVALID_ARGUMENT status.
 */
inline Status StatusInvalidArgument(const string& msg) {
  return STATUS_FROM_ENUM(INVALID_ARGUMENT, msg);
}

/*
 * Creates a standard OUT_OF_RANGE status.
 */
inline Status StatusOutOfRange(const string& msg) {
  return STATUS_FROM_ENUM(OUT_OF_RANGE, msg);
}

/*
 * Creates a standard PERMISSION_DENIED status.
 */
inline Status StatusPermissionDenied(const string& msg) {
  return STATUS_FROM_ENUM(PERMISSION_DENIED, msg);
}

/*
 * Creates a standard UNIMPLEMENTED status.
 */
inline Status StatusUnimplemented(const string& msg) {
  return STATUS_FROM_ENUM(UNIMPLEMENTED, msg);
}

/*
 * Creates a standard UNKNOWN status.
 */
inline Status StatusUnknown(const string& msg) {
  return STATUS_FROM_ENUM(UNKNOWN, msg);
}

/*
 * Creates a standard RESOURCE_EXHAUSTED status.
 */
inline Status StatusResourceExhausted(const string& msg) {
  return STATUS_FROM_ENUM(RESOURCE_EXHAUSTED, msg);
}

/*
 * Creates a standard FAILED_PRECONDITION status.
 */
inline Status StatusFailedPrecondition(const string& msg) {
  return STATUS_FROM_ENUM(FAILED_PRECONDITION, msg);
}

}  // namespace util

}  // namespace network

#endif  // NETWORK_API_STATUS_H_
