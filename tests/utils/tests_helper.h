#ifndef EESAVEEDITOR_TESTS_HELPER_H
#define EESAVEEDITOR_TESTS_HELPER_H

#include <fstream>
#include <string_view>

using namespace std;

struct TempCreator
{
    TempCreator(const char* name, const char* signature, const char* version) : name(name)
    {
        ofstream ofs(name, ios::binary);
        ofs.write(signature, 4);
        ofs.write(version, 4);
        ofs.close();
    }

    ~TempCreator()
    {
        filesystem::remove(filesystem::path(name));
    }

    TempCreator() = delete;
    TempCreator(const TempCreator&) = delete;
    TempCreator& operator=(const TempCreator&) = delete;
    TempCreator(TempCreator&&) = delete;
    TempCreator& operator=(TempCreator&&) = delete;

    const string_view name;
};

#endif //EESAVEEDITOR_TESTS_HELPER_H