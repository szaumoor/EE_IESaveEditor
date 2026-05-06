#include "settings.h"

#include <stdexcept>

#include <QSettings>
#include <QString>
#include <utility>

#include "games.h"

GamePaths::GamePaths( const game::Type game )
    : m_game(game_path(game)), m_save(save_path(game)) { }

GamePaths::GamePaths(QString game_path, QString save_path)
    : m_game(std::move(game_path)), m_save(std::move(save_path)) { }

QString game_path( const game::Type game ) {
    settings.beginGroup( consts::SettingsGameFolders );
    QString game_path;

    switch( game )
    {
        case game::Type::None:
            game_path = ""; // Nope.
            break;
        case game::Type::Bgee:
            game_path = settings.value( consts::SettingsGameBGEE, consts::HomeDir ).toString();
            break;
        case game::Type::Bg2ee:
            game_path = settings.value( consts::SettingsGameBG2EE, consts::HomeDir ).toString();
            break;
        case game::Type::Iwdee:
            game_path = settings.value( consts::SettingsGameIWDEE, consts::HomeDir ).toString();
            break;
        default:
            std::unreachable();
    }

    settings.endGroup();
    return game_path;
}

QString selected_game_path()
{
    return game_path(selected_game());
}

QString save_path( const game::Type game ) {
    settings.beginGroup( consts::SettingsGameFolders );
    QString game_path;
    switch( game )
    {
        case game::Type::Bgee:
            game_path = settings.value( consts::SettingsSavesBGEE, consts::HomeDir ).toString();
            break;
        case game::Type::Bg2ee:
            game_path = settings.value( consts::SettingsSavesBG2EE, consts::HomeDir ).toString();
            break;
        case game::Type::Iwdee:
            game_path = settings.value( consts::SettingsSavesIWDEE, consts::HomeDir ).toString();
            break;
        default:
            settings.endGroup();
            throw std::runtime_error( "Something went horribly wrong" );
    }
    settings.endGroup();
    return game_path;
}

i8 selected_game_index()
{
    settings.beginGroup( consts::SettingsGameFolders );
    const auto selected = settings.value( consts::SettingsSelectedGame, -1 )
                                  .toInt();
    settings.endGroup();
    return static_cast<i8>(selected);
}

game::Type selected_game()
{
    const auto parsed= game::parse( selected_game_index() );
    return parsed.value_or( game::Type::None );
}

void write_save_paths(const GamePaths& bgee_paths, const GamePaths& bg2ee_paths, const GamePaths& iwdee_paths)
{
    settings.beginGroup(consts::SettingsGameFolders);
    {
        settings.setValue(consts::SettingsGameBGEE, bgee_paths.game());
        settings.setValue(consts::SettingsSavesBGEE, bgee_paths.save());
        settings.setValue(consts::SettingsGameBG2EE, bg2ee_paths.game());
        settings.setValue(consts::SettingsSavesBG2EE, bg2ee_paths.save());
        settings.setValue(consts::SettingsGameIWDEE, iwdee_paths.game());
        settings.setValue(consts::SettingsSavesIWDEE, iwdee_paths.save());
    }
    settings.endGroup();
}

void write_game_lang(Language::Type lang)
{
    settings.beginGroup(consts::SettingsGameFolders);
    settings.setValue(consts::SettingsGameLanguage, Language::code_for_lang(lang));
    settings.endGroup();
}

Language::Type game_lang()
{
    settings.beginGroup(consts::SettingsGameFolders);
    const auto lang = settings.value(consts::SettingsGameLanguage,
                                     QVariant(Language::number(Language::Type::English))).toInt();
    settings.endGroup();
    return Language::parse(lang)
        .value_or( Language::Type::English );
}

