#include <filesystem>
#include <fstream>

#include "tests_helper.h"

using std::string_view;
using std::ofstream;
namespace fs = std::filesystem;

TempCreator::TempCreator(const string_view name,
                         const string_view signature,
                         const string_view version) : name(name)
{
    ofstream ofs(name.data(), std::ios::binary);
    ofs.write(signature.data(), 4);
    ofs.write(version.data(), 4);
}

TempCreator::~TempCreator()
{
    fs::remove(std::filesystem::path(name));
}
