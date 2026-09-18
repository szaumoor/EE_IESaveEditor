#include "resource_repository.hpp"

#include "../../backend/utils/errors.hpp"

constexpr std::array<std::string_view, 5> biffs
{
    "25Items.bif",
    "25Spells.bif",
    "Items.bif",
    "Spells.bif",
    "Patch25.bif"
};

Possible<ResourceRepository>
ResourceRepository::open( std::filesystem::path path, Language lang )
{
    ResourceRepository repo( std::move(path) );

    const auto tlk_path = repo.m_root_path/ "lang"/ "en_US"/ "dialog.tlk";
    auto tlkFile = TlkFile::open( tlk_path.string() );
    if ( not tlkFile )
    {
        return NotPossible(IEError(IEErrorType::Unknown,
            std::format("Tlk failed to load. Error seems to be '{}'",
                    tlkFile.error().what() )));
    }

    repo.m_tlk.emplace( std::move(tlkFile.value()) );

    auto keyFile = KeyFile::open( (repo.m_root_path/ "chitin.key").string() );
    if ( not keyFile )
    {
        return NotPossible(IEError(IEErrorType::Unknown,
            std::format("Key file failed to be open. Error seems to be '{}'",
            keyFile.error().what())));
    }

    repo.m_key_file.emplace( std::move(keyFile.value()) );

    for (const auto& biff : biffs)
    {
        const auto possible_bif = BiffFile::open((repo.m_root_path/"data"/biff).string());
        if (not possible_bif)
        {
            return NotPossible(IEError(IEErrorType::Unknown,
                std::format("Bif file '{}' failed to open. Error seems to be '{}'",
                    biff, possible_bif.error().what())  ));
        }

        repo.m_bifs.push_back( possible_bif.value() );
    }

    return repo;
}

ResourceRepository::ResourceRepository( std::filesystem::path  path )
    : m_root_path(std::move(path)) {  }

