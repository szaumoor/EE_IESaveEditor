#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStandardPaths>
#include <QString>

namespace consts
{
    namespace settings
    {
        constexpr auto kAuthor          = "Kaelyn";
        constexpr auto kAppName         = "IE Save Editor";
        constexpr auto kLocationFolders = "GameFolders";
        constexpr auto kLocationBGEE    = "GameBGEE";
        constexpr auto kLocationBG2EE   = "GameBG2EE";
        constexpr auto kLocationIWDEE   = "GameIWDEE";
        constexpr auto kSavesBGEE       = "SavesBGEE";
        constexpr auto kSavesBG2EE      = "SavesBG2EE";
        constexpr auto kSavesIWDEE      = "SavesIWDEE";
        constexpr auto kSelectedGame    = "SelectedGame";
        constexpr auto kLanguage        = "GameLanguage";
    }

    namespace files
    {
        inline const QString kHomeDir  = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        constexpr auto kGam            = "BALDUR.gam";
        constexpr auto kTLK            = "dialog.tlk";
        constexpr auto kLangEnglish    = "en_US";
        constexpr auto kLangGerman     = "de_DE";
        constexpr auto kLangSpanish    = "es_ES";
        constexpr auto kLangFrench     = "fr_FR";
        constexpr auto kLangItalian    = "it_IT";
        constexpr auto kLangKorean     = "ko_KR";
        constexpr auto kLangPortuguese = "pt_PT";
        constexpr auto kLangRussian    = "ru_RU";
        constexpr auto kLangChinese    = "zh_CN";
    }
}

#endif // CONSTANTS_H
