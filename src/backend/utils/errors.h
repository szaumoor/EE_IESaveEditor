#ifndef EESAVEEDITOR_ERRORS_H
#define EESAVEEDITOR_ERRORS_H

#include <expected>
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
    std::string_view what() const noexcept;

    /**
     * Returns the error type associated with the error.
     * @return IEErrorType associated with the error.
     */
    [[nodiscard("Dont ignore error types")]]
    IEErrorType type() const noexcept;

private:
    const IEErrorType m_error_type;
    std::string_view m_error_message;
};


/**
 * Parametrized class that encapsulates a possible (std::expected) value along with a possible
 * error message. Only IEFile classes or IEStringView may be used as parameter.
 *
 * @tparam T Type must be IEStringView or assignable to IEFile
 */
template<typename T>
class [[nodiscard("Do not ignore a Possible (expected) value")]] Possible : public std::expected<T, IEError>
{
    static_assert( std::is_base_of_v<IEFile, T> || std::same_as<T, IEStringView>);
    using std::expected<T, IEError>::expected;
};

#endif //EESAVEEDITOR_ERRORS_H
