/**
 * @file TextColor.cpp
 * @brief A simple C++ wrapper for terminal text colorize implementation
 */

#include "TextColor.h"

using Color::TextColor;

TextColor::TextColor(const Color::TextColorCode& colorCode) :
    _code(colorCode)
{
}

void TextColor::SetCode(const Color::TextColorCode& colorCode)
{
    _code = colorCode;
}

Color::TextColorCode TextColor::GetCode() const
{
    return _code;
}
