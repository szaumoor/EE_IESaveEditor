#ifndef EESAVEEDITOR_ERRORS_H
#define EESAVEEDITOR_ERRORS_H

#include <string>
#include <string_view>

#include "aliases.h"

enum class [[nodiscard]] IEErrorType : u8
{
    NotFound    = 0,
    Unreadable  = 1,
    Malformed   = 2,
    OutOfBounds = 3
};

class IEError
{
public:
    explicit IEError(IEErrorType error_t, std::string_view error_m);
    explicit IEError(IEErrorType error_t);

    [[nodiscard]]
    constexpr std::string_view what() const { return error_message; };

    [[nodiscard]]
    constexpr IEErrorType type() const { return error_type; };

private:
    const IEErrorType error_type;
    std::string_view error_message;
};

#endif //EESAVEEDITOR_ERRORS_H