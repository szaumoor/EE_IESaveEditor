#include "cre_file.h"
#include "utils/aliases.h"
#include "utils/io.h"

#include <fstream>
#include <utility>
#include <vector>

Effect Effect::from( const EmbeddedEffFileV1& eff )
{
    Effect effect;
    common_mapping( effect, eff );
    effect.resource = eff.keyword;
    return effect;
}

Effect Effect::from( const EmbeddedEffFileV2& eff )
{
    Effect effect;
    common_mapping( effect, eff );
    effect.resource = eff.resource1;
    return effect;
}

CreFile CreFile::read( std::ifstream& file, const u32 offset )
{
    CreFile cre;
    auto& header = cre._header;
    const StructWriter writer( file );
    writer.into( header );

    cre.resize_vecs();

    writer.into( cre.m_known_spells, offset + cre._header.known_spells_offset );
    writer.into( cre.m_memorization_infos, offset + header.memorization_offset );
    writer.into( cre.m_memorized_spells, offset + cre._header.memorized_offset );
    writer.into( cre.m_items, offset + cre._header.items_offset );
    writer.into( cre.m_item_slots, offset + cre._header.item_slots_offset );

    file.seekg( offset + cre._header.effects_offset, std::ios::beg );

    switch ( header.eff_structure_version )
    {
        [[unlikely]] case 0:
            cre.read_effects<EmbeddedEffFileV1>( cre, writer );
            break;
        [[likely]] case 1:
            cre.read_effects<EmbeddedEffFileV2>( cre, writer );
            break;
        default:
            std::unreachable(); // should check for corrupt values anyway
    }

    return cre;
}

std::vector<Effect> CreFile::effects()
{
    std::vector<Effect> out;
    out.reserve( m_effects.size() );

    for ( const auto& eff : m_effects )
    {
        std::visit( [&]( const auto& instance ) {
            out.push_back( std::move( Effect::from( instance ) ) );
        }, eff );
    }
    return out;
}

void CreFile::resize_vecs() noexcept
{
    m_known_spells.resize( _header.known_spells_count );
    m_memorization_infos.resize( _header.memorization_count );
    m_memorized_spells.resize( _header.memorized_count );
    m_items.resize( _header.items_count );
}
