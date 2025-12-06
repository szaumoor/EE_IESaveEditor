#include "utils/aliases.h"
#include "cre_file.h"

#include <fstream>
#include <vector>

#include "utils/io.h"

void CreFile::resize_vecs() noexcept
{
    _known_spells.resize(_header.known_spells_count );
    _memorization_infos.resize( _header.memorization_count );
    _memorized_spells.resize( _header.memorized_count );
    _items.resize( _header.items_count );
}

CreFile CreFile::read(std::ifstream &file, const u32 offset)
{
    CreFile cre;
    auto& header = cre._header;
    const StructWriter writer(file);
    writer.into(header);

    cre.resize_vecs();

    writer.into(cre._known_spells, offset + cre._header.known_spells_offset);
    writer.into(cre._memorization_infos, offset + header.memorization_offset);
    writer.into(cre._memorized_spells, offset + cre._header.memorized_offset);
    writer.into(cre._items, offset + cre._header.items_offset);
    writer.into(cre._item_slots, offset + cre._header.item_slots_offset);

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
