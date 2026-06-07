#include "biff_file.h"

#include <fstream>
#include <print>

#include "ie_files.h"
#include "utils/io.h"

using std::ifstream;

static constexpr std::string_view kBiffSignature( "BIFF" );
static constexpr std::string_view kBiffFileVersion( "V1  " );


Possible<BiffFile> BiffFile::open( const std::string_view path )
{
    ifstream file_handle( path.data(), std::ios::binary );

    if ( not file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    BiffFile biff( path );
    auto& header = biff.m_header;
    StructWriter writer( file_handle );
    writer.into( header );
    biff.check_for_malformation();

    if ( not biff )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    if ( header.count_of_file_entries > 0 )
    {
        biff.m_file_entries.resize( header.count_of_file_entries );
        writer.into( biff.m_file_entries, header.offset_to_file_entries );
    }

    if ( header.count_of_tile_entries > 0 )
    {
        biff.m_tile_entries.resize( header.count_of_tile_entries );
        writer.into( biff.m_tile_entries,
                     header.offset_to_file_entries + static_cast<u32>(sizeof( FileEntry )) * header.count_of_file_entries );
    }
    for (const auto& entry : biff.m_file_entries)
    {
        switch (entry.resource_type)
        {
            case ResourceType::FileTypeSpl:
            {
                SplHeader spl_header{};
                writer.into(spl_header, entry.offset);
                biff.m_spells.push_back( spl_header );
                break;
            }

            case ResourceType::FileTypeIds:
            {
                std::string text;
                text.resize(entry.size);
                file_handle.seekg(entry.offset, std::ios::beg);
                file_handle.read(text.data(), entry.size);
                biff.m_ids_files.push_back( std::move(text) );
                break;
            }

            case ResourceType::FileTypeIni:
            {
                std::string text;
                text.resize(entry.size);
                file_handle.seekg(entry.offset, std::ios::beg);
                file_handle.read(text.data(), entry.size);
                biff.m_ini_files.push_back( std::move(text) );
                break;
            }

            case ResourceType::FileTypeBmp:
            case ResourceType::FileTypeBam:
            case ResourceType::FileTypeItm:
            case ResourceType::FileType2da:
            case ResourceType::FileTypePng:
            case ResourceType::NotFound:
                break;

            case ResourceType::FileTypeAre:
            case ResourceType::FileTypeBah:
            case ResourceType::FileTypeBcs:
            case ResourceType::FileTypeBio:
            case ResourceType::FileTypeBs:
            case ResourceType::FileTypeChr1:
            case ResourceType::FileTypeWmap:
            case ResourceType::FileTypeMve:
            case ResourceType::FileTypeWav:
            case ResourceType::FileTypeWfx:
            case ResourceType::FileTypePlt:
            case ResourceType::FileTypeWed:
            case ResourceType::FileTypeChu:
            case ResourceType::FileTypeTi:
            case ResourceType::FileTypeMos:
            case ResourceType::FileTypeCre:
            case ResourceType::FileTypeDlg:
            case ResourceType::FileTypeGam:
            case ResourceType::FileTypeSto:
            case ResourceType::FileTypeChr:
            case ResourceType::FileTypeVvc:
            case ResourceType::FileTypeVef:
            case ResourceType::FileTypePro:
            case ResourceType::FileTypeWbm:
            case ResourceType::FileTypeFnt:
            case ResourceType::FileTypeGui:
            case ResourceType::FileTypeSql:
            case ResourceType::FileTypePvrz:
            case ResourceType::FileTypeGlsl:
            case ResourceType::FileTypeTlk:
            case ResourceType::FileTypeMenu:
            case ResourceType::FileTypeMenu2:
            case ResourceType::FileTypeTtf:
            case ResourceType::FileTypeSrc:
                break;
        }
    }

    return biff;
}

void BiffFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kBiffSignature;
    const bool valid_version   = m_header.version.to_string() == kBiffFileVersion;

    m_good = valid_signature && valid_version;
}
