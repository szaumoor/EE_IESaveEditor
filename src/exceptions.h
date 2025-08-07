#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InvalidStateOperationError : public std::logic_error
{
public:
    explicit InvalidStateOperationError( const std::string& what_arg )
        : std::logic_error( what_arg ) {}
};

#endif
