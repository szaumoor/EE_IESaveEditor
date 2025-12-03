#ifndef EESAVEEDITOR_ERRORS_H
#define EESAVEEDITOR_ERRORS_H

#include <string>
#include <string_view>

enum class [[nodiscard]] IEErrorType
{
    NotFound,
    Unreadable,
    Malformed,
    OutOfBounds
};

struct IEError
{
    const IEErrorType error_type;
    const std::string error_message;

    explicit IEError(const IEErrorType error_t, const std::string_view error_m)
        : error_type(error_t), error_message(error_m) {}
};

#endif //EESAVEEDITOR_ERRORS_H