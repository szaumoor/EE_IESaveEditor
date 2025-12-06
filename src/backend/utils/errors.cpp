//
// Created by marcos on 12/5/25.
//

#include "errors.h"

#include <utility>

constexpr std::string_view resolve_error_msg(const IEErrorType t)
{
    switch (t) {
        case IEErrorType::NotFound:
            return "File not found.";
        case IEErrorType::Unreadable:
            return "File could not be read.";
        case IEErrorType::Malformed:
            return "Malformed file.";
        case IEErrorType::OutOfBounds:
            return "Out of bounds.";
        default:
            std::unreachable();
    }
}

IEError::IEError(const IEErrorType error_t)
        : error_type(error_t), error_message(resolve_error_msg(error_type)) {}

IEError::IEError(const IEErrorType error_t, const std::string_view error_m)
    : error_type(error_t), error_message(error_m) {}
