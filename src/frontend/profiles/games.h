#ifndef GAMES_H
#define GAMES_H

#include <expected>

#include <QMap>
#include <QString>

#include "../../backend/utils/aliases.h"

class Game final
{
public:
    enum struct Instance : i8 { Bgee=0, Bg2ee=1,Iwdee=2 };

    class Language final
    {
    public:
        enum class Instance : i8
        {
            English = 0, German = 1, French     = 2, Italian = 3,
            Spanish = 4, Korean = 5, Portuguese = 6, Russian = 7, SChinese = 8
        };

        Language() = delete;

        static std::expected<Instance, QString> parse( const int language )
        {
            if ( language < 0 || language > 8  )
                return std::unexpected( "Invalid value for language" );
            return static_cast<Instance>( language );
        }

        static i8 to_code( Instance lang ) { return static_cast<i8>( lang ); }

        static QString to_str ( const Instance lang )
        {
            switch ( lang )
            {
                case Instance::English:    return "English";
                case Instance::French:     return "French";
                case Instance::German:     return "German";
                case Instance::Italian:    return "Italian";
                case Instance::Korean:     return "Korean";
                case Instance::Portuguese: return "Portuguese";
                case Instance::Russian:    return "Russian";
                case Instance::Spanish:    return "Spanish";
                case Instance::SChinese:   return "Simplified Chinese";
            }
            return {};
        }
        static QString code_for_lang( const Instance lang )
        {
            static QMap<Instance, QString> lang_map = create_map();
            return lang_map.find( lang ).value();
        };

    private:
        static QMap<Instance, QString> create_map()
        {
            using namespace consts;
            QMap<Instance, QString> lang_map;
            lang_map.insert( Instance::English,    files::kLangEnglish    );
            lang_map.insert( Instance::German,     files::kLangGerman     );
            lang_map.insert( Instance::French,     files::kLangFrench     );
            lang_map.insert( Instance::Korean,     files::kLangKorean     );
            lang_map.insert( Instance::Russian,    files::kLangRussian    );
            lang_map.insert( Instance::Italian,    files::kLangItalian    );
            lang_map.insert( Instance::Spanish,    files::kLangSpanish    );
            lang_map.insert( Instance::Portuguese, files::kLangPortuguese );
            lang_map.insert( Instance::SChinese,   files::kLangChinese    );
            return lang_map;
        }
    };

    static std::expected<Instance, QString> parse( const int game )
    {
        if ( game < 0 || game > 2 )
            return std::unexpected("Valid values for Game are 0-2 (bgee, bg2ee, iwdee)");
        return static_cast<Instance>(game);
    }

    static i8 to_code( const Instance game )
    {
        return static_cast<i8>( game );
    }
};

#endif // GAMES_H
