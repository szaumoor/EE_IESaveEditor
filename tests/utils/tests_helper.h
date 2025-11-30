#ifndef EESAVEEDITOR_TESTS_HELPER_H
#define EESAVEEDITOR_TESTS_HELPER_H

#include <fstream>
#include <string_view>

using namespace std;

struct TempCreator
{
public:
    TempCreator() = delete;
    TempCreator(const char* name, const char* signature, const char* version) : name(name)
    {
        std::ofstream ofs(name, ios::binary);
        ofs.write(signature, 4);
        ofs.write(version, 4);
        ofs.close();
    }

    ~TempCreator()
    {
        filesystem::remove(filesystem::path(name));
    }

    const string_view name;

private:
    ;
};

#endif //EESAVEEDITOR_TESTS_HELPER_H