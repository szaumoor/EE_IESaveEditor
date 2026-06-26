#ifndef EESAVEEDITOR_ERRORS_H
#define EESAVEEDITOR_ERRORS_H

#include <string_view>

#include "aliases.h"
#include "../ie_string.h"

class IEFile;
/**
 * Enum class that provide constants for different errors related to
 * interacting with the IE files.
 */
enum struct [[nodiscard("Do not discard error types")]]
    IEErrorType : u8
{
    NotFound    = 0,
    Unreadable  = 1,
    Malformed   = 2,
    OutOfBounds = 3
};

/**
 * Class that encapsulates the possible errors associated with the various
 * error types that may arise when interacting with the IE files.
 */
class IEError
{
public:
    explicit IEError( IEErrorType error_type, std::string_view error_m ) noexcept;
    explicit IEError( IEErrorType error_type ) noexcept;

    /**
     * Return the error message associated with the error type.
     * @return std::string_view with the error message
     */
    [[nodiscard("Don't ignore error messages")]]
    std::string what() const noexcept;

    /**
     * Returns the error type associated with the error.
     * @return IEErrorType associated with the error.
     */
    [[nodiscard("Dont ignore error types")]]
    IEErrorType type() const noexcept;

private:
    const IEErrorType m_error_type;
    std::string m_error_message;
};

#endif //EESAVEEDITOR_ERRORS_H
