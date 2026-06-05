#include "settings.h"
#include "games.h"

#include <QSettings>
#include <QString>

#include <utility>

namespace sett
{
    using namespace consts;

    inline QSettings qs( settings::kAuthor, settings::kAppName );

    GamePaths::GamePaths( const Game::Instance game )
        : m_game(game_path(game)), m_save(save_path(game)) { }

    GamePaths::GamePaths(QString game_path, QString save_path)
        : m_game(std::move(game_path)), m_save(std::move(save_path)) { }

    QString game_path( const Game::Instance game ) {
        qs.beginGroup( settings::kLocationFolders );
        QString path;

        switch( game )
        {
            case Game::Instance::Bgee:
                path = qs.value( settings::kLocationBGEE, files::kHomeDir ).toString();
                break;
            case Game::Instance::Bg2ee:
                path = qs.value( settings::kLocationBG2EE, files::kHomeDir ).toString();
                break;
            case Game::Instance::Iwdee:
                path = qs.value( settings::kLocationIWDEE, files::kHomeDir ).toString();
                break;
            default:
                std::unreachable();
        }

        qs.endGroup();
        return path;
    }

    QString selected_game_path()
    {
       return game_path(selected_game());
    }

    QString save_path( const Game::Instance game ) {
        qs.beginGroup( settings::kLocationFolders );
        QString path;
        switch( game )
        {
            case Game::Instance::Bgee:
                path = qs.value( settings::kSavesBGEE, files::kHomeDir ).toString();
                break;
            case Game::Instance::Bg2ee:
                path = qs.value( settings::kSavesBG2EE, files::kHomeDir ).toString();
                break;
            case Game::Instance::Iwdee:
                path = qs.value( settings::kSavesIWDEE, files::kHomeDir ).toString();
                break;
            default:
                std::unreachable();
        }
        qs.endGroup();
        return path;
    }

    i8 selected_game_index()
    {
        qs.beginGroup( settings::kLocationFolders );
        const auto selected = qs.value( settings::kSelectedGame, -1 )
                                      .toInt();
        qs.endGroup();
        return static_cast<i8>(selected);
    }

    Game::Instance selected_game()
    {
        const auto parsed= Game::parse( selected_game_index() );
        return parsed.value();
    }

    void write_save_paths(const GamePaths& bgee_paths, const GamePaths& bg2ee_paths, const GamePaths& iwdee_paths)
    {
        qs.beginGroup(settings::kLocationFolders);

        qs.setValue(settings::kLocationBGEE, bgee_paths.game());
        qs.setValue(settings::kSavesBGEE, bgee_paths.save());

        qs.setValue(settings::kSavesBG2EE, bg2ee_paths.game());
        qs.setValue(settings::kSavesBG2EE, bg2ee_paths.save());

        qs.setValue(settings::kSavesIWDEE, iwdee_paths.game());
        qs.setValue(settings::kSavesIWDEE, iwdee_paths.save());

        qs.endGroup();
    }

    void write_game_lang( const Game::Language::Instance lang)
    {
        qs.beginGroup(settings::kLocationFolders);
        qs.setValue(settings::kLanguage, Game::Language::code_for_lang(lang));
        qs.endGroup();
    }

    Game::Language::Instance game_lang()
    {
        qs.beginGroup(settings::kLocationFolders);
        const auto lang = qs.value(settings::kLanguage,
                                QVariant(Game::Language::to_code(Game::Language::Instance::English)))
                                .toInt();
        qs.endGroup(); // I'm already storing it with a default value thoooo
        return Game::Language::parse(lang).value();
    }
}
