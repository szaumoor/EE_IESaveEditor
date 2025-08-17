#include "aliases.h"
#include "cre_file.h"

#include <fstream>
#include <vector>
#include "eff_files.h"

CreFile::CreFile( std::ifstream& file, const u32 offset ) :header( {} ), item_slots({})
{
    file.seekg( offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&header), sizeof(CreHeader) );

    known_spells.resize( header.known_spells_count );
    file.seekg( offset + header.known_spells_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(known_spells.data()),
        header.known_spells_count * sizeof(CreKnownSpell) );

    memorization_infos.resize( header.memorization_count );
    file.seekg( offset + header.memorization_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(memorization_infos.data()),
        header.memorization_count * sizeof( CreSpellMemorizationInfo ) );

    memorized_spells.resize( header.memorized_count );
    file.seekg( offset + header.memorized_offset );
    file.read( reinterpret_cast<char*>(memorized_spells.data()),
        header.memorized_count * sizeof( CreSpellMemorizedSpell ) );

    items.resize( header.items_count );
    file.seekg( offset + header.items_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(items.data()),
        header.items_count * sizeof( CreInventoryItem ) );

    file.seekg( offset + header.item_slots_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&item_slots), sizeof( CreItemSlots ) );

    file.seekg( offset + header.effects_offset, std::ios::beg );
    if ( header.eff_structure_version == 0 )
    {
        std::vector<EmbeddedEffFileV1> effects_v1;
        effects_v1.resize( header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v1.data()),
            header.effects_count * sizeof( EmbeddedEffFileV1 ) );
        for ( const auto& eff : effects_v1 )
            effects.push_back( eff );
    }
    else if ( header.eff_structure_version == 1 )
    {
        std::vector<EmbeddedEffFileV2> effects_v2;
        effects_v2.resize( header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v2.data()),
            header.effects_count * sizeof( EmbeddedEffFileV2 ) );
        for ( const auto& eff : effects_v2 )
            effects.push_back( eff );
    }
}
