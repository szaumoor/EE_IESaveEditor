#ifndef IE_FILES_H
#define IE_FILES_H

#include <concepts>
#include <expected>
#include <fstream>
#include <string_view>
#include <type_traits>

#include "utils/errors.h"
#include "utils/ie_class.h"


/**
 * This concept defines statically the basic API requirements to define a class to encapsulate
 * a Infinity Engine binary file. Such class must obey the following requirements:
 *
 * - Must define a method such as check_for_malformation() -> void which should be used
 *   to make sure the reading of the file has completed with the expected structure.
 * - Must overload the bool operator
 * - Must define a method called good(), which asserts whether the file read is in a good
 * state or not.
 **/
template <typename T>
concept IE = std::derived_from<std::remove_cvref_t<T>, IEClass> &&
    requires(T obj, const T& cobj) {
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
class [[nodiscard("Do not ignore a Possible (expected) value")]]
Possible : public std::expected<T, IEError>
{
    static_assert(std::derived_from<std::remove_cvref_t<T>, IEClass>);
    using std::expected<T, IEError>::expected;
};

class [[nodiscard("Do not ignore a NotPossible (unexpected) value")]]
NotPossible : public std::unexpected<IEError>
{
    using std::unexpected<IEError>::unexpected;
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
  { T::read(file_handle, offset) } -> std::same_as<Possible<T>>;
};

#endif // IE_FILES_H
