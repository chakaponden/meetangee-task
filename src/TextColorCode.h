/**
 * @file TextColorCode.h
 * @brief Enum some possible ASCII text colors
 */

#ifndef TEXTCOLORCODE_H
#define TEXTCOLORCODE_H

namespace Color
{
    /**
     * @enum Color::TextColorCode
     * @brief Enum some possible ASCII text colors
     * @version 0.1.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details FG prefix means foreground color
     *          BG prefix means background color
     * @todo Add more color codes
     */
    enum TextColorCode
    {
        FG_RED      = 31,   ///< foreground red
        FG_GREEN    = 32,   ///< foreground green
        FG_YELLOW   = 33,   ///< foreground yellow
        FG_BLUE     = 34,   ///< foreground blue
        FG_DEFAULT  = 39,   ///< foreground default
        BG_RED      = 41,   ///< background red
        BG_GREEN    = 42,   ///< background green
        BG_BLUE     = 44    ///< background blue
    };
}

#endif // TEXTCOLORCODE_H
