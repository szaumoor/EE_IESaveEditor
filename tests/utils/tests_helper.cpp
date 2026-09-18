#include <filesystem>
#include <fstream>

#include "tests_helper.hpp"

namespace fs = std::filesystem;

namespace ZS
{
    TempCreator::TempCreator(const std::string_view name,
                             const std::string_view signature,
                             const std::string_view version) : m_name(name)
    {
        std::ofstream ofs(name.data(), std::ios::binary);
        ofs.write(signature.data(), 4);
        ofs.write(version.data(), 4);
    }

    TempCreator::~TempCreator()
    {
        fs::remove(fs::path(m_name));
    }
}