#ifndef SETTINGS_H
#define SETTINGS_H

#include "constants.hpp"
#include "games.hpp"

namespace sett
{
    class GamePaths
    {
    public:
        GamePaths() = delete;
        GamePaths(GamePaths& other) = delete;
        GamePaths(GamePaths&& other) = delete;

        explicit GamePaths( GameInstance game );
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

    QString game_path( GameInstance game );
    std::optional<QString> selected_game_path();
    QString save_path( GameInstance game );
    i8 selected_game_index();
    std::optional<GameInstance> selected_game();
    void write_save_paths( const GamePaths& bgeePaths, const GamePaths& bg2eePaths, const GamePaths& iwdeePaths );
    void write_game_lang( Language lang );
    Language game_lang();
    bool clear_settings();
}

#endif // SETTINGS_H
