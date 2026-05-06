#ifndef SETTINGS_H
#define SETTINGS_H

#include "constants.h"
#include "games.h"

#include <QSettings>

inline QSettings settings( consts::SettingsAuthor, consts::SettingsAppName );

class GamePaths
{
public:
    GamePaths() = delete;
    GamePaths(GamePaths& other) = delete;
    GamePaths(GamePaths&& other) = delete;
    
    explicit GamePaths( game::Type game );
    GamePaths( QString game_path, QString save_path );
    
    [[nodiscard]]
    bool both_filled() const { return !m_game.isEmpty() && !m_save.isEmpty(); }

    [[nodiscard]]
    QString game() const { return m_game; }

    [[nodiscard]]
    QString save() const { return m_save; }
    
private:
    const QString m_game;
    const QString m_save;
};

class Language
{
public:
    enum class Type : u8
    {
        English    = 0, German  = 1, French            = 2,
        Italian    = 3, Spanish = 4, Korean            = 5,
        Portuguese = 6, Russian = 7, SimplifiedChinese = 8
    };
    
    Language() = delete;
    
    static std::expected<Type, QString> parse( const u8 language )
    {
        if ( language > 8  )
            return std::unexpected( "Invalid value for language" );
        return static_cast<Type>( language );
    }
    
    static u8 number( Type lang ) { return static_cast<u8>( lang ); }
    
    static QString string_representation ( const Type lang )
    {
        switch ( lang )
        {
            case Type::English:           return "English";
            case Type::French:            return "French";
            case Type::German:            return "German";
            case Type::Italian:           return "Italian";
            case Type::Korean:            return "Korean";
            case Type::Portuguese:        return "Portuguese";
            case Type::Russian:           return "Russian";
            case Type::Spanish:           return "Spanish";
            case Type::SimplifiedChinese: return "Simplified Chinese";
        }
        return {};
    }
    static QString code_for_lang( Type lang )
    {
        static QMap<Type, QString> lang_map = create_map();
        return lang_map.find( lang ).value();
    };

private:
    static QMap<Type, QString> create_map()
    {
        QMap<Type, QString> lang_map;
        lang_map.insert( Type::English,           consts::LangEng        );
        lang_map.insert( Type::German,            consts::LangGerman     );
        lang_map.insert( Type::French,            consts::LangFr         );
        lang_map.insert( Type::Korean,            consts::LangKorean     );
        lang_map.insert( Type::Russian,           consts::LangRussian    );
        lang_map.insert( Type::Italian,           consts::LangIt         );
        lang_map.insert( Type::Spanish,           consts::LangEs         );
        lang_map.insert( Type::Portuguese,        consts::LangPortuguese );
        lang_map.insert( Type::SimplifiedChinese, consts::LangChinese    );
        return lang_map;
    }
};

QString game_path( game::Type game );
QString selected_game_path();
QString save_path( game::Type game );
i8 selected_game_index();
game::Type selected_game();
void write_save_paths( const GamePaths& bgeePaths, const GamePaths& bg2eePaths, const GamePaths& iwdeePaths );
void write_game_lang( Language::Type lang );
Language::Type game_lang();

#endif // SETTINGS_H
