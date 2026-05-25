#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStandardPaths>
#include <QString>

namespace consts
{
    inline QString kHomeDir              = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    constexpr auto kSettingsAuthor       = "Kaelyn";
    constexpr auto kSettingsAppName      = "IE Save Editor";
    constexpr auto kSettingsGameFolders  = "GameFolders";
    constexpr auto kSettingsGameBGEE     = "GameBGEE";
    constexpr auto kSettingsSavesBGEE    = "SavesBGEE";
    constexpr auto kSettingsGameBG2EE    = "GameBG2EE";
    constexpr auto kSettingsSavesBG2EE   = "SavesBG2EE";
    constexpr auto kSettingsGameIWDEE    = "GameIWDEE";
    constexpr auto kSettingsSavesIWDEE   = "SavesIWDEE";
    constexpr auto kSettingsSelectedGame = "SelectedGame";
    constexpr auto kSettingsGameLanguage = "GameLanguage";

    constexpr auto kGamFilename    = "BALDUR.gam";
    constexpr auto kDialogTLK      = "dialog.tlk";
    constexpr auto kLangEng        = "en_US";
    constexpr auto kLangGerman     = "de_DE";
    constexpr auto kLangEs         = "es_ES";
    constexpr auto kLangFr         = "fr_FR";
    constexpr auto kLangIt         = "it_IT";
    constexpr auto kLangKorean     = "ko_KR";
    constexpr auto kLangPortuguese = "pl_PL";
    constexpr auto kLangRussian    = "ru_RU";
    constexpr auto kLangChinese    = "zh_CN";
}

#endif // CONSTANTS_H
