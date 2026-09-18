#include "../helpers/qt_strings.hpp"

#include "constants.hpp"
#include "games.hpp"


constexpr auto fHardLimitCodeAllowedLanguages = 8;
constexpr std::array game_languages{
    GameLanguageInfo{
        .language = Language::English,
        .locale_code = consts::files::kLangEnglish
    },
    GameLanguageInfo{
        .language = Language::German,
        .locale_code = consts::files::kLangGerman
    },
    GameLanguageInfo{
        .language = Language::French,
        .locale_code = consts::files::kLangFrench
    },
    GameLanguageInfo{
        .language = Language::Italian,
        .locale_code = consts::files::kLangItalian
    },
    GameLanguageInfo{
        .language = Language::Spanish,
        .locale_code = consts::files::kLangSpanish
    },
    GameLanguageInfo{
        .language = Language::Korean,
        .locale_code = consts::files::kLangKorean
    },
    GameLanguageInfo{
        .language = Language::Portuguese,
        .locale_code = consts::files::kLangPortuguese
    },
    GameLanguageInfo{
        .language = Language::Russian,
        .locale_code = consts::files::kLangRussian
    },
    GameLanguageInfo{
        .language = Language::SimplifiedChinese,
        .locale_code = consts::files::kLangChinese
    },
};

u8 id_from_lang( const Language lang )
{
    return std::to_underlying( lang );
}

std::optional<Language> lang_from_id( const u8 id )
{
    if ( id > fHardLimitCodeAllowedLanguages )
    {
        return std::nullopt;
    }
    return static_cast<Language>(id);
}

Language lang_from_locale( const QLocale& locale )
{
    switch ( locale.language() )
    {
        case QLocale::Spanish:
            return Language::Spanish;
        case QLocale::Chinese:
            return Language::SimplifiedChinese;
        case QLocale::English:
        default:
            return Language::English;
    }
}

std::optional<QString> code_for_lang( const Language lang )
{
    const auto lang_code = id_from_lang( lang );
    if ( lang_code >= game_languages.size() )
        return std::nullopt;

    return str::from( game_languages[lang_code].locale_code );
}

std::optional<GameInstance> game_from_id( const int game )
{
    if ( game < 0 || game > 2 )
        return std::nullopt;

    return static_cast<GameInstance>(game);
}
