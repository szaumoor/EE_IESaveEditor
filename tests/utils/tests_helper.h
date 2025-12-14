#ifndef EESAVEEDITOR_TESTS_HELPER_H
#define EESAVEEDITOR_TESTS_HELPER_H

#include <string_view>

struct TempCreator
{
    TempCreator(std::string_view name, std::string_view signature, std::string_view version);
    ~TempCreator();

    TempCreator() = delete;
    TempCreator(const TempCreator&) = delete;
    TempCreator& operator=(const TempCreator&) = delete;
    TempCreator(TempCreator&&) = delete;
    TempCreator& operator=(TempCreator&&) = delete;

    const std::string_view name;
};

#endif //EESAVEEDITOR_TESTS_HELPER_H
