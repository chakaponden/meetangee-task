/**
 * TextColor.hpp
 *
 * A simple C++ wrapper for terminal text colorize.
 */

#ifndef TEXTCOLOR_HPP
#define TEXTCOLOR_HPP
#include <ostream>

namespace Color
{
    enum TextColorCode
    {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44
    };

    class TextColor
    {
    public:
        TextColor(TextColorCode pCode) : _code(pCode) {}
        friend std::ostream& operator <<(std::ostream& os, const TextColor& mod)
        {
            return os << "\033[" << mod._code << "m";
        }
    private:
        Color::TextColorCode _code;
    };
    /*
     * const Color::TextColor red(Color::TextColorCode::FG_RED);
     * const Color::TextColor def(Color::TextColorCode::FG_DEFAULT);
     * usage:
     * std::cout << red << "this text has red color"
     *           << def << "this text is default color";
     */
}
#endif  /* TEXTCOLOR_HPP */