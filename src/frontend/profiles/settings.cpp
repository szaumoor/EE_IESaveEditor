#include "settings.hpp"
#include "games.hpp"

#include <QSettings>

namespace sett
{
    using namespace consts;
    GamePaths::GamePaths( const GameInstance game )
        : m_game(game_path(game)), m_save(save_path(game)) { }

    GamePaths::GamePaths(QString game_path, QString save_path)
        : m_game(std::move(game_path)), m_save(std::move(save_path)) { }

    QString game_path( const GameInstance game ) {
        QSettings qs( settings::kAuthor, settings::kAppName );
        qs.beginGroup( settings::kLocationFolders );
        QString path;

        switch( game )
        {
            case GameInstance::Bgee:
                path = qs.value( settings::kLocationBGEE, QString{} ).toString();
                break;
            case GameInstance::Bg2ee:
                path = qs.value( settings::kLocationBG2EE, QString{} ).toString();
                break;
            case GameInstance::Iwdee:
                path = qs.value( settings::kLocationIWDEE, QString{} ).toString();
                break;
            default:
                std::unreachable();
        }

        qs.endGroup();
        return path;
    }

    std::optional<QString> selected_game_path()
    {
      // return game_path( selected_game().value_or("") ); // ??
        return std::nullopt;
    }

    QString save_path( const GameInstance game ) {
        QSettings qs( settings::kAuthor, settings::kAppName );
        qs.beginGroup( settings::kLocationFolders );
        QString path;
        switch( game )
        {
            case GameInstance::Bgee:
                path = qs.value( settings::kSavesBGEE, QString{}).toString();
                break;
            case GameInstance::Bg2ee:
                path = qs.value( settings::kSavesBG2EE, QString{} ).toString();
                break;
            case GameInstance::Iwdee:
                path = qs.value( settings::kSavesIWDEE, QString{} ).toString();
                break;
            default:
                std::unreachable();
        }
        qs.endGroup();
        return path;
    }

    i8 selected_game_index()
    {
        QSettings qs( settings::kAuthor, settings::kAppName );
        qs.beginGroup( settings::kLocationFolders );
        const auto selected = qs.value( settings::kSelectedGame, -1 )
                                .toInt();
        qs.endGroup();
        return static_cast<i8>(selected);
    }

    std::optional<GameInstance> selected_game()
    {
        return game_from_id( selected_game_index() );
    }

    void write_save_paths(const GamePaths& bgee_paths, const GamePaths& bg2ee_paths, const GamePaths& iwdee_paths)
    {
        QSettings qs( settings::kAuthor, settings::kAppName );

        qs.beginGroup(settings::kLocationFolders);
        auto writePath = [&](const char* gameKey, const char* saveKey, const GamePaths& paths) {
            if (paths.game().isEmpty())
                qs.remove(gameKey);
            else
                qs.setValue(gameKey, paths.game());

            if (paths.save().isEmpty())
                qs.remove(saveKey);
            else
                qs.setValue(saveKey, paths.save());
        };
        writePath(settings::kLocationBGEE, settings::kSavesBGEE, bgee_paths);
        writePath(settings::kLocationBG2EE, settings::kSavesBG2EE, bg2ee_paths);
        writePath(settings::kLocationIWDEE, settings::kSavesIWDEE, iwdee_paths);
        qs.endGroup();
    }

    void write_game_lang( const Language lang)
    {
        QSettings qs( settings::kAuthor, settings::kAppName );

        qs.beginGroup(settings::kLocationFolders);
        qs.setValue(settings::kLanguage, id_from_lang(lang));
        qs.endGroup();
    }

    Language game_lang()
    {
        QSettings qs( settings::kAuthor, settings::kAppName );
        qs.beginGroup(settings::kLocationFolders);
        const auto lang = qs.value(settings::kLanguage,
                            QVariant(id_from_lang(Language::English)))
                                .toInt();
        qs.endGroup();

        const u8 converted_value = static_cast<u8>(lang);
        return lang_from_id( converted_value ).value();
    }

    bool clear_settings()
    {
        QSettings qs( settings::kAuthor, settings::kAppName );
        qs.remove( settings::kLocationFolders );
        qs.sync();
        return qs.status() == QSettings::NoError;
    }
}
