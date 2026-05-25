#include "settings.h"
#include "games.h"

#include <QSettings>
#include <QString>

#include <utility>

namespace sett
{
    inline QSettings qs( consts::kSettingsAuthor, consts::kSettingsAppName );

    GamePaths::GamePaths( const Game::Type game )
        : m_game(game_path(game)), m_save(save_path(game)) { }

    GamePaths::GamePaths(QString game_path, QString save_path)
        : m_game(std::move(game_path)), m_save(std::move(save_path)) { }

    QString game_path( const Game::Type game ) {
        qs.beginGroup( consts::kSettingsGameFolders );
        QString path;

        switch( game )
        {
            case Game::Type::Bgee:
                path = qs.value( consts::kSettingsGameBGEE, consts::kHomeDir ).toString();
                break;
            case Game::Type::Bg2ee:
                path = qs.value( consts::kSettingsGameBG2EE, consts::kHomeDir ).toString();
                break;
            case Game::Type::Iwdee:
                path = qs.value( consts::kSettingsGameIWDEE, consts::kHomeDir ).toString();
                break;
        }

        qs.endGroup();
        return path;
    }

    QString selected_game_path()
    {
      //  return game_path(selected_game());
        return ";";
    }

    QString save_path( const Game::Type game ) {
        qs.beginGroup( consts::kSettingsGameFolders );
        QString path;
        switch( game )
        {
            case Game::Type::Bgee:
                path = qs.value( consts::kSettingsSavesBGEE, consts::kHomeDir ).toString();
                break;
            case Game::Type::Bg2ee:
                path = qs.value( consts::kSettingsSavesBG2EE, consts::kHomeDir ).toString();
                break;
            case Game::Type::Iwdee:
                path = qs.value( consts::kSettingsSavesIWDEE, consts::kHomeDir ).toString();
                break;
        }
        qs.endGroup();
        return path;
    }

    i8 selected_game_index()
    {
        qs.beginGroup( consts::kSettingsGameFolders );
        const auto selected = qs.value( consts::kSettingsSelectedGame, -1 )
                                      .toInt();
        qs.endGroup();
        return static_cast<i8>(selected);
    }

    std::optional<Game::Type> selected_game()
    {
        const auto parsed= Game::parse( selected_game_index() );
        if ( !parsed )
            return std::nullopt;
        return parsed.value();
    }

    void write_save_paths(const GamePaths& bgee_paths, const GamePaths& bg2ee_paths, const GamePaths& iwdee_paths)
    {
        qs.beginGroup(consts::kSettingsGameFolders);
        qs.setValue(consts::kSettingsGameBGEE, bgee_paths.game());
        qs.setValue(consts::kSettingsSavesBGEE, bgee_paths.save());
        qs.setValue(consts::kSettingsGameBG2EE, bg2ee_paths.game());
        qs.setValue(consts::kSettingsSavesBG2EE, bg2ee_paths.save());
        qs.setValue(consts::kSettingsGameIWDEE, iwdee_paths.game());
        qs.setValue(consts::kSettingsSavesIWDEE, iwdee_paths.save());
        qs.endGroup();
    }

    void write_game_lang( const Language::Type lang)
    {
        qs.beginGroup(consts::kSettingsGameFolders);
        qs.setValue(consts::kSettingsGameLanguage, Language::code_for_lang(lang));
        qs.endGroup();
    }

    Language::Type game_lang()
    {
        qs.beginGroup(consts::kSettingsGameFolders);
        const auto lang = qs.value(consts::kSettingsGameLanguage,
                                QVariant(Language::number(Language::Type::English)))
                                .toInt();
        qs.endGroup(); // I'm already storing it with a default value thoooo
        return Language::parse(lang)
                        .value_or( Language::Type::English );
    }
}
