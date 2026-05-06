#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStandardPaths>
#include <QString>

namespace consts
{
    inline QString HomeDir              = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    constexpr auto SettingsAuthor       = "Kaelyn";
    constexpr auto SettingsAppName      = "IE Save Editor";
    constexpr auto SettingsGameFolders  = "GameFolders";
    constexpr auto SettingsGameBGEE     = "GameBGEE";
    constexpr auto SettingsSavesBGEE    = "SavesBGEE";
    constexpr auto SettingsGameBG2EE    = "GameBG2EE";
    constexpr auto SettingsSavesBG2EE   = "SavesBG2EE";
    constexpr auto SettingsGameIWDEE    = "GameIWDEE";
    constexpr auto SettingsSavesIWDEE   = "SavesIWDEE";
    constexpr auto SettingsSelectedGame = "SelectedGame";
    constexpr auto SettingsGameLanguage = "GameLanguage";

    constexpr auto GamFilename    = "BALDUR.gam";
    constexpr auto DialogTLK      = "dialog.tlk";
    constexpr auto LangEng        = "en_US";
    constexpr auto LangGerman     = "de_DE";
    constexpr auto LangEs         = "es_ES";
    constexpr auto LangFr         = "fr_FR";
    constexpr auto LangIt         = "it_IT";
    constexpr auto LangKorean     = "ko_KR";
    constexpr auto LangPortuguese = "pl_PL";
    constexpr auto LangRussian    = "ru_RU";
    constexpr auto LangChinese    = "zh_CN";
}

#endif // CONSTANTS_H
