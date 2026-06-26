#include "errors.h"

#include <utility>

constexpr std::string_view resolve_error_msg( const IEErrorType t ) noexcept
{
    switch ( t )
    {
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

IEError::IEError( const IEErrorType error_type, const std::string_view error_m ) noexcept
    : m_error_type( error_type ), m_error_message( error_m ) { }

IEError::IEError( const IEErrorType error_type ) noexcept
    : m_error_type( error_type ), m_error_message( resolve_error_msg( m_error_type ) ) { }

std::string IEError::what() const noexcept { return m_error_message; }
IEErrorType IEError::type() const noexcept { return m_error_type; }
