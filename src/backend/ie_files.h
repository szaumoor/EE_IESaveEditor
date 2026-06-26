#ifndef IE_FILES_H
#define IE_FILES_H

#include <concepts>
#include <expected>
#include <fstream>

#include "utils/errors.h"

template <typename T>
concept IE = requires(T obj, const T& cobj) {
    { obj.check_for_malformation() } noexcept -> std::same_as<void>;
    static_cast<bool(T::*)() const noexcept>(&T::operator bool);
    { cobj.good() } noexcept -> std::same_as<bool>;
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
    static_assert(IE<T> || std::same_as<T, IEStringView>);
    using std::expected<T, IEError>::expected;
};

template <typename T>
concept IE_Openable = IE<T> && requires(const T& cobj, std::string_view path)
{
  { T::open(path) } -> std::same_as<Possible<T>>;
  { cobj.path() } noexcept -> std::same_as<std::string_view>;
};

template<typename T>
concept IE_Readable = IE<T> && requires(std::ifstream file_handle, u32 offset)
{
  {T::read(file_handle, offset) } -> std::same_as<Possible<T>>;
};

#endif // IE_FILES_H
