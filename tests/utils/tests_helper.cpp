#include <filesystem>

#include "tests_helper.h"

using namespace std;

TempCreator::TempCreator(const char* name,
                         const char* signature,
                         const char* version) : name(name)
{
    ofstream ofs(name, ios::binary);
    ofs.write(signature, 4);
    ofs.write(version, 4);
    ofs.close();
}

TempCreator::~TempCreator()
{
    filesystem::remove(filesystem::path(name));
}
