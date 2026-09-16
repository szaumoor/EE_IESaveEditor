#ifndef GAMES_H
#define GAMES_H

#include "../../backend/utils/aliases.hpp"

enum struct GameInstance : i8 {
    Bgee = 0, Bg2ee = 1, Iwdee = 2
};

enum struct Language : u8 {
    English = 0,
    German = 1,
    French = 2,
    Italian = 3,
    Spanish = 4,
    Korean = 5,
    Portuguese = 6,
    Russian = 7,
    SimplifiedChinese = 8
};

struct GameLanguageInfo {
    Language language;
    std::string_view locale_code;
};


u8 id_from_lang(Language lang);
std::optional<Language> lang_from_id(u8 id);
Language lang_from_locale(const QLocale& locale);
std::optional<QString> code_for_lang(Language lang);

u8 id_from_game(GameInstance game);
std::optional<GameInstance> game_from_id(int game);

#endif // GAMES_H
