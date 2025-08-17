#include "aliases.h"
#include "cre_file.h"
#include "eff_files.h"

#include <fstream>
#include <vector>

CreFile::CreFile( std::ifstream& file, const u32 offset ) noexcept
    : header( {} ), item_slots({})
{
    file.seekg( offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&header), sizeof(CreHeader) );

    known_spells.resize( header.known_spells_count );
    memorization_infos.resize( header.memorization_count );
    memorized_spells.resize( header.memorized_count );
    items.resize( header.items_count );

    file.seekg( offset + header.known_spells_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(known_spells.data()),
        header.known_spells_count * sizeof(CreKnownSpell) );

    file.seekg( offset + header.memorization_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(memorization_infos.data()),
        header.memorization_count * sizeof( CreSpellMemorizationInfo ) );

    file.seekg( offset + header.memorized_offset );
    file.read( reinterpret_cast<char*>(memorized_spells.data()),
        header.memorized_count * sizeof( CreSpellMemorizedSpell ) );

    file.seekg( offset + header.items_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(items.data()),
        header.items_count * sizeof( CreInventoryItem ) );

    file.seekg( offset + header.item_slots_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&item_slots), sizeof( CreItemSlots ) );

    file.seekg( offset + header.effects_offset, std::ios::beg );
    if ( header.eff_structure_version == 0 )
    {
        vector<EmbeddedEffFileV1> effects_v1;
        effects_v1.resize( header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v1.data()),
            header.effects_count * sizeof( EmbeddedEffFileV1 ) );
        effects.insert( effects.end(), effects_v1.begin(), effects_v1.end() );
    }
    else if ( header.eff_structure_version == 1 )
    {
        vector<EmbeddedEffFileV2> effects_v2;
        effects_v2.resize( header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v2.data()),
            header.effects_count * sizeof( EmbeddedEffFileV2 ) );
        effects.insert( effects.end(), effects_v2.begin(), effects_v2.end() );
    }
}
