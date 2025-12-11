#include <filesystem>
#include <fstream>

#include "tests_helper.h"

using std::string_view;

TempCreator::TempCreator(const string_view name,
                         const string_view signature,
                         const string_view version) : name(name)
{
    std::ofstream ofs(name.data(), std::ios::binary);
    ofs.write(signature.data(), 4);
    ofs.write(version.data(), 4);
}

TempCreator::~TempCreator()
{
    std::filesystem::remove(std::filesystem::path(name));
}
