#include "cre_file.h"
#include "utils/aliases.h"
#include "utils/io.h"

#include <fstream>
#include <utility>
#include <vector>

constexpr auto kCreSig = "CRE ";
constexpr auto kCreVersion = "V1.0";

Effect Effect::from( const EmbeddedEffFileV1& eff ) noexcept
{
    Effect effect;
    common_mapping( effect, eff );
    effect.resource = eff.keyword;
    return effect;
}

Effect Effect::from( const EmbeddedEffFileV2& eff ) noexcept
{
    Effect effect;
    common_mapping( effect, eff );
    effect.resource = eff.resource1;
    return effect;
}

Possible<CreFile> CreFile::read( std::ifstream& file, const u32 offset )
{
    CreFile cre;
    auto& cre_header = cre.m_header;
    const StructWriter writer( file );
    writer.into( cre_header );
    cre.check_for_malformation();

    if (!cre)
    {
        return std::unexpected(IEError(IEErrorType::Malformed,
                   std::format("Embedded creature file is corrupted,"
                               " signature={}, version={}", cre_header.signature.to_string(),
                               cre_header.version.to_string())));
    }

    cre.resize_vecs();
    writer.into( cre.m_known_spells, offset + cre_header.known_spells_offset );
    writer.into( cre.m_memorization_infos, offset + cre_header.memorization_offset );
    writer.into( cre.m_memorized_spells, offset + cre_header.memorized_offset );
    writer.into( cre.m_items, offset + cre_header.items_offset );
    writer.into( cre.m_item_slots, offset + cre_header.item_slots_offset );

    file.seekg( offset + cre_header.effects_offset, std::ios::beg );
    switch ( const auto eff_v = cre_header.eff_struct_version )
    {
        [[unlikely]]
        case 0:
            cre.read_effects<EmbeddedEffFileV1>( cre, writer );
            break;
        [[likely]]
        case 1:
            cre.read_effects<EmbeddedEffFileV2>( cre, writer );
            break;
        default:
        {
            return std::unexpected(IEError(IEErrorType::Malformed,
                    std::format("Creature file has unknown effect structure {}", eff_v ) ) ) ;
        }
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

void CreFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kCreSig;
    const bool valid_version   = m_header.version.to_string() == kCreVersion;

    m_good = valid_signature && valid_version;
}

void CreFile::resize_vecs() noexcept
{
    m_known_spells.resize( m_header.known_spells_count );
    m_memorization_infos.resize( m_header.memorization_count );
    m_memorized_spells.resize( m_header.memorized_count );
    m_items.resize( m_header.items_count );
}
