#include "python.h"

class PyTheme : public Theme {
public:
    using Theme::Theme;
};

/* The "old-school" `static const char *` approach is being used here so that
 * these values can be bound with pybind11.  In the C++ code it is preferable to
 * have ``static constexpr auto Normal = "sans"`` etc., but it is not possible
 * to bind this with pybind11.
 *
 * Instead of forcing the C++ code to use the "old" way, we simply bind this
 * TU-local ``global_default_fonts_proxy`` struct instead.
 */
struct global_default_fonts_proxy {
    static const char *Normal;
    static const char *Bold;
    static const char *Mono;
    static const char *MonoBold;
    static const char *Icons;
};

const char *global_default_fonts_proxy::Normal   = Theme::GlobalDefaultFonts::Normal;
const char *global_default_fonts_proxy::Bold     = Theme::GlobalDefaultFonts::Bold;
const char *global_default_fonts_proxy::Mono     = Theme::GlobalDefaultFonts::Mono;
const char *global_default_fonts_proxy::MonoBold = Theme::GlobalDefaultFonts::MonoBold;
const char *global_default_fonts_proxy::Icons    = Theme::GlobalDefaultFonts::Icons;

void register_theme(py::module &m) {
    py::class_<Theme, ref<Theme>, PyTheme> theme(m, "Theme", D(Theme));
    theme.def(py::init<NVGcontext *>(), D(Theme, Theme))
         .def_readwrite("mDefaultFont", &Theme::mDefaultFont, D(Theme, mDefaultFont))
         .def_readwrite("mDefaultBoldFont", &Theme::mDefaultBoldFont, D(Theme, mDefaultBoldFont))
         .def_readwrite("mDefaultMonoFont", &Theme::mDefaultMonoFont, D(Theme, mDefaultMonoFont))
         .def_readwrite("mDefaultMonoBoldFont", &Theme::mDefaultMonoBoldFont, D(Theme, mDefaultMonoBoldFont))
         .def_readwrite("mDefaultIconFont", &Theme::mDefaultIconFont, D(Theme, mDefaultIconFont))
         .def_readwrite("mIconScale", &Theme::mIconScale, D(Theme, mIconScale))
         .def_readwrite("mStandardFontSize", &Theme::mStandardFontSize, D(Theme, mStandardFontSize))
         .def_readwrite("mButtonFontSize", &Theme::mButtonFontSize, D(Theme, mButtonFontSize))
         .def_readwrite("mTextBoxFontSize", &Theme::mTextBoxFontSize, D(Theme, mTextBoxFontSize))
         .def_readwrite("mWindowFontSize", &Theme::mWindowFontSize, D(Theme, mWindowFontSize))
         .def_readwrite("mWindowCornerRadius", &Theme::mWindowCornerRadius, D(Theme, mWindowCornerRadius))
         .def_readwrite("mWindowHeaderHeight", &Theme::mWindowHeaderHeight, D(Theme, mWindowHeaderHeight))
         .def_readwrite("mWindowDropShadowSize", &Theme::mWindowDropShadowSize, D(Theme, mWindowDropShadowSize))
         .def_readwrite("mButtonCornerRadius", &Theme::mButtonCornerRadius, D(Theme, mButtonCornerRadius))
         .def_readwrite("mTabBorderWidth", &Theme::mTabBorderWidth, D(Theme, mTabBorderWidth))
         .def_readwrite("mTabInnerMargin", &Theme::mTabInnerMargin, D(Theme, mTabInnerMargin))
         .def_readwrite("mTabMinButtonWidth", &Theme::mTabMinButtonWidth, D(Theme, mTabMinButtonWidth))
         .def_readwrite("mTabMaxButtonWidth", &Theme::mTabMaxButtonWidth, D(Theme, mTabMaxButtonWidth))
         .def_readwrite("mTabControlWidth", &Theme::mTabControlWidth, D(Theme, mTabControlWidth))
         .def_readwrite("mTabButtonHorizontalPadding", &Theme::mTabButtonHorizontalPadding, D(Theme, mTabButtonHorizontalPadding))
         .def_readwrite("mTabButtonVerticalPadding", &Theme::mTabButtonVerticalPadding, D(Theme, mTabButtonVerticalPadding))
         .def_readwrite("mDropShadow", &Theme::mDropShadow, D(Theme, mDropShadow))
         .def_readwrite("mTransparent", &Theme::mTransparent, D(Theme, mTransparent))
         .def_readwrite("mBorderDark", &Theme::mBorderDark, D(Theme, mBorderDark))
         .def_readwrite("mBorderLight", &Theme::mBorderLight, D(Theme, mBorderLight))
         .def_readwrite("mBorderMedium", &Theme::mBorderMedium, D(Theme, mBorderMedium))
         .def_readwrite("mTextColor", &Theme::mTextColor, D(Theme, mTextColor))
         .def_readwrite("mDisabledTextColor", &Theme::mDisabledTextColor, D(Theme, mDisabledTextColor))
         .def_readwrite("mTextColorShadow", &Theme::mTextColorShadow, D(Theme, mTextColorShadow))
         .def_readwrite("mIconColor", &Theme::mIconColor, D(Theme, mIconColor))
         .def_readwrite("mButtonGradientTopFocused", &Theme::mButtonGradientTopFocused, D(Theme, mButtonGradientTopFocused))
         .def_readwrite("mButtonGradientBotFocused", &Theme::mButtonGradientBotFocused, D(Theme, mButtonGradientBotFocused))
         .def_readwrite("mButtonGradientTopUnfocused", &Theme::mButtonGradientTopUnfocused, D(Theme, mButtonGradientTopUnfocused))
         .def_readwrite("mButtonGradientBotUnfocused", &Theme::mButtonGradientBotUnfocused, D(Theme, mButtonGradientBotUnfocused))
         .def_readwrite("mButtonGradientTopPushed", &Theme::mButtonGradientTopPushed, D(Theme, mButtonGradientTopPushed))
         .def_readwrite("mButtonGradientBotPushed", &Theme::mButtonGradientBotPushed, D(Theme, mButtonGradientBotPushed))
         .def_readwrite("mTooltipOpacity", &Theme::mTooltipOpacity, D(Theme, mTooltipOpacity))
         .def_readwrite("mTooltipBackgroundColor", &Theme::mTooltipBackgroundColor, D(Theme, mTooltipBackgroundColor))
         .def_readwrite("mTooltipTextColor", &Theme::mTooltipTextColor, D(Theme, mTooltipTextColor))
         .def_readwrite("mWindowFillUnfocused", &Theme::mWindowFillUnfocused, D(Theme, mWindowFillUnfocused))
         .def_readwrite("mWindowFillFocused", &Theme::mWindowFillFocused, D(Theme, mWindowFillFocused))
         .def_readwrite("mWindowTitleUnfocused", &Theme::mWindowTitleUnfocused, D(Theme, mWindowTitleUnfocused))
         .def_readwrite("mWindowTitleFocused", &Theme::mWindowTitleFocused, D(Theme, mWindowTitleFocused))
         .def_readwrite("mWindowHeaderGradientTop", &Theme::mWindowHeaderGradientTop, D(Theme, mWindowHeaderGradientTop))
         .def_readwrite("mWindowHeaderGradientBot", &Theme::mWindowHeaderGradientBot, D(Theme, mWindowHeaderGradientBot))
         .def_readwrite("mWindowHeaderSepTop", &Theme::mWindowHeaderSepTop, D(Theme, mWindowHeaderSepTop))
         .def_readwrite("mWindowHeaderSepBot", &Theme::mWindowHeaderSepBot, D(Theme, mWindowHeaderSepBot))
         .def_readwrite("mWindowPopup", &Theme::mWindowPopup, D(Theme, mWindowPopup))
         .def_readwrite("mWindowPopupTransparent", &Theme::mWindowPopupTransparent, D(Theme, mWindowPopupTransparent))
         .def_readwrite("mCheckBoxIcon", &Theme::mCheckBoxIcon, D(Theme, mCheckBoxIcon))
         .def_readwrite("mCheckBoxIconExtraScale", &Theme::mCheckBoxIconExtraScale, D(Theme, mCheckBoxIconExtraScale))
         .def_readwrite("mMessageInformationIcon", &Theme::mMessageInformationIcon, D(Theme, mMessageInformationIcon))
         .def_readwrite("mMessageQuestionIcon", &Theme::mMessageQuestionIcon, D(Theme, mMessageQuestionIcon))
         .def_readwrite("mMessageWarningIcon", &Theme::mMessageWarningIcon, D(Theme, mMessageWarningIcon))
         .def_readwrite("mMessageAltButtonIcon", &Theme::mMessageAltButtonIcon, D(Theme, mMessageAltButtonIcon))
         .def_readwrite("mMessagePrimaryButtonIcon", &Theme::mMessagePrimaryButtonIcon, D(Theme, mMessagePrimaryButtonIcon))
         .def_readwrite("mPopupChevronRightIcon", &Theme::mPopupChevronRightIcon, D(Theme, mPopupChevronRightIcon))
         .def_readwrite("mPopupChevronLeftIcon", &Theme::mPopupChevronLeftIcon, D(Theme, mPopupChevronLeftIcon))
         .def_readwrite("mPopupIconExtraScale", &Theme::mPopupIconExtraScale, D(Theme, mPopupIconExtraScale))
         .def_readwrite("mTabHeaderLeftIcon", &Theme::mTabHeaderLeftIcon, D(Theme, mTabHeaderLeftIcon))
         .def_readwrite("mTabHeaderRightIcon", &Theme::mTabHeaderRightIcon, D(Theme, mTabHeaderRightIcon))
         .def_readwrite("mTextBoxUpIcon", &Theme::mTextBoxUpIcon, D(Theme, mTextBoxUpIcon))
         .def_readwrite("mTextBoxDownIcon", &Theme::mTextBoxDownIcon, D(Theme, mTextBoxDownIcon))
         .def_readwrite("mTextBoxIconExtraScale", &Theme::mTextBoxIconExtraScale, D(Theme, mTextBoxIconExtraScale))
         .def_readwrite("mPlotBackgroundColor", &Theme::mPlotBackgroundColor, D(Theme, mPlotBackgroundColor))
         .def_readwrite("mPlotForegroundColor", &Theme::mPlotForegroundColor, D(Theme, mPlotForegroundColor))
         .def_readwrite("mPlotTextColor", &Theme::mPlotTextColor, D(Theme, mPlotTextColor))
         .def_readwrite("mPlotMajorTickColor", &Theme::mPlotMajorTickColor, D(Theme, mPlotMajorTickColor))
         .def_readwrite("mPlotMinorTickColor", &Theme::mPlotMinorTickColor, D(Theme, mPlotMinorTickColor));



    /* See declaration of global_default_fonts_proxy at the top of this file.
     *
     * NOTE: using this approach, the static member documentation is attached to
     *       the metaclass: help(nanogui.Theme.GlobalDefaultFonts.__class__.Bold)
     *
     * Since help(nanogui.Theme.GlobalDefaultFonts.Bold) does not exist (because
     * of the metaclassing going on), the main GlobalDefaultFonts docstring
     * should continue to enumerate the five possible constants.
     */
    py::class_<global_default_fonts_proxy>(theme, "GlobalDefaultFonts", py::metaclass(), D(Theme, GlobalDefaultFonts))
        .def_readonly_static("Normal",   &global_default_fonts_proxy::Normal,   D(Theme, GlobalDefaultFonts, Normal))
        .def_readonly_static("Bold",     &global_default_fonts_proxy::Bold,     D(Theme, GlobalDefaultFonts, Bold))
        .def_readonly_static("Mono",     &global_default_fonts_proxy::Mono,     D(Theme, GlobalDefaultFonts, Mono))
        .def_readonly_static("MonoBold", &global_default_fonts_proxy::MonoBold, D(Theme, GlobalDefaultFonts, MonoBold))
        .def_readonly_static("Icons",    &global_default_fonts_proxy::Icons,    D(Theme, GlobalDefaultFonts, Icons));
}
