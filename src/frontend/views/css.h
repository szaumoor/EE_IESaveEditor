#ifndef EE_SAVEEDITOR_CSS_H
#define EE_SAVEEDITOR_CSS_H

namespace css
{
    constexpr auto kTabWidget = R"(
        QTabBar::tab {
            font-weight: normal;
        }
        QTabBar::tab:selected {
            font-weight: bold;
        }
    )";

    constexpr auto kPartyMemberSlider = R"(
        QSlider::groove:horizontal {
            border: 1px solid #777;
            height: 8px;
            background: #c8c8c8;
            border-radius: 4px;
        }

        QSlider::sub-page:horizontal {
            background: #2d7dd2;
            border: 1px solid #2d7dd2;
            height: 8px;
            border-radius: 4px;
        }

        QSlider::add-page:horizontal {
            background: #d6d6d6;
            border: 1px solid #999;
            height: 8px;
            border-radius: 4px;
        }

        QSlider::handle:horizontal {
            background: #ffffff;
            border: 2px solid #2d7dd2;
            width: 18px;
            height: 18px;
            margin: -6px 0;
            border-radius: 9px;
        }

        QSlider::handle:horizontal:hover {
            background: #eaf3ff;
            border: 2px solid #1b5fa7;
        }

        QSlider::handle:horizontal:pressed {
            background: #2d7dd2;
            border: 2px solid #174f8a;
        }
    )";
}

#endif //EE_SAVEEDITOR_CSS_H
