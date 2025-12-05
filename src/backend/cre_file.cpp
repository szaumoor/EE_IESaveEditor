#include "utils/aliases.h"
#include "cre_file.h"

#include <fstream>
#include <vector>

CreFile CreFile::read(std::ifstream &file, const u32 offset)
{
    CreFile cre(file, offset);

    file.seekg( offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&cre._header), sizeof(CreHeader) );

    cre._known_spells.resize( cre._header.known_spells_count );
    cre._memorization_infos.resize( cre._header.memorization_count );
    cre._memorized_spells.resize( cre._header.memorized_count );
    cre._items.resize( cre._header.items_count );

    file.seekg( offset + cre._header.known_spells_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(cre._known_spells.data()),
        static_cast<std::streamsize>(cre._header.known_spells_count * sizeof(CreKnownSpell)));

    file.seekg( offset + cre._header.memorization_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(cre._memorization_infos.data()),
        static_cast<std::streamsize>(cre._header.memorization_count * sizeof( CreSpellMemorizationInfo )));

    file.seekg( offset + cre._header.memorized_offset );
    file.read( reinterpret_cast<char*>(cre._memorized_spells.data()),
        static_cast<std::streamsize>(cre._header.memorized_count * sizeof( CreSpellMemorizedSpell ) ));

    file.seekg( offset + cre._header.items_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(cre._items.data()),
        static_cast<std::streamsize>(cre._header.items_count * sizeof( CreInventoryItem ) ));

    file.seekg( offset + cre._header.item_slots_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&cre._item_slots), sizeof( CreItemSlots ) );

    file.seekg( offset + cre._header.effects_offset, std::ios::beg );

    if ( cre._header.eff_structure_version == 0 ) [[unlikely]]
    {
        std::vector<EmbeddedEffFileV1> effects_v1;
        effects_v1.resize( cre._header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v1.data()),
            static_cast<std::streamsize>(cre._header.effects_count * sizeof( EmbeddedEffFileV1 ) ));
        cre._effects.insert( cre._effects.end(), effects_v1.begin(), effects_v1.end() );
    }
    else if (  cre._header.eff_structure_version == 1 ) [[likely]]
    {
        std::vector<EmbeddedEffFileV2> effects_v2;
        effects_v2.resize( cre._header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v2.data()),
            static_cast<std::streamsize>(cre._header.effects_count * sizeof( EmbeddedEffFileV2 ) ));
        cre._effects.insert( cre._effects.end(), effects_v2.begin(), effects_v2.end() );
    }

    return std::move(cre);
}

CreFile::CreFile( std::ifstream& file, const u32 offset ) noexcept
    : _header( {} ), _item_slots({})
{
    file.seekg( offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&_header), sizeof(CreHeader) );

    _known_spells.resize( _header.known_spells_count );
    _memorization_infos.resize( _header.memorization_count );
    _memorized_spells.resize( _header.memorized_count );
    _items.resize( _header.items_count );

    file.seekg( offset + _header.known_spells_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(_known_spells.data()),
        static_cast<std::streamsize>(_header.known_spells_count * sizeof(CreKnownSpell)));

    file.seekg( offset + _header.memorization_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(_memorization_infos.data()),
        static_cast<std::streamsize>(_header.memorization_count * sizeof( CreSpellMemorizationInfo )));

    file.seekg( offset + _header.memorized_offset );
    file.read( reinterpret_cast<char*>(_memorized_spells.data()),
        static_cast<std::streamsize>(_header.memorized_count * sizeof( CreSpellMemorizedSpell ) ));

    file.seekg( offset + _header.items_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(_items.data()),
        static_cast<std::streamsize>(_header.items_count * sizeof( CreInventoryItem ) ));

    file.seekg( offset + _header.item_slots_offset, std::ios::beg );
    file.read( reinterpret_cast<char*>(&_item_slots), sizeof( CreItemSlots ) );

    file.seekg( offset + _header.effects_offset, std::ios::beg );

    if ( _header.eff_structure_version == 0 ) [[unlikely]]
    {
        std::vector<EmbeddedEffFileV1> effects_v1;
        effects_v1.resize( _header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v1.data()),
            static_cast<std::streamsize>(_header.effects_count * sizeof( EmbeddedEffFileV1 ) ));
        _effects.insert( _effects.end(), effects_v1.begin(), effects_v1.end() );
    }
    else if (  _header.eff_structure_version == 1 ) [[likely]]
    {
        std::vector<EmbeddedEffFileV2> effects_v2;
        effects_v2.resize( _header.effects_count );
        file.read( reinterpret_cast<char*>(effects_v2.data()),
            static_cast<std::streamsize>(_header.effects_count * sizeof( EmbeddedEffFileV2 ) ));
        _effects.insert( _effects.end(), effects_v2.begin(), effects_v2.end() );
    }
}


