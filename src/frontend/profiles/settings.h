#ifndef SETTINGS_H
#define SETTINGS_H

#include "constants.h"
#include "games.h"

namespace sett
{
    class GamePaths
    {
    public:
        GamePaths() = delete;
        GamePaths(GamePaths& other) = delete;
        GamePaths(GamePaths&& other) = delete;
    
        explicit GamePaths( Game::Instance game );
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

    QString game_path( Game::Instance game );
    QString selected_game_path();
    QString save_path( Game::Instance game );
    i8 selected_game_index();
    Game::Instance selected_game();
    void write_save_paths( const GamePaths& bgeePaths, const GamePaths& bg2eePaths, const GamePaths& iwdeePaths );
    void write_game_lang( Game::Language::Instance lang );
    Game::Language::Instance game_lang();
}

#endif // SETTINGS_H
