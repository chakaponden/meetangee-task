/**
 * @file TextColor.h
 * @brief A simple C++ wrapper for terminal text colorize
 */

#ifndef TEXTCOLOR_H
#define TEXTCOLOR_H

#include <ostream>

#include "TextColorCode.h"

namespace Color
{
    /**
     * @brief A simple C++ wrapper for terminal text colorize
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details Provide terminal text colorize functionality as functor
     *
     * Example usage:
     * @code
     * const Color::TextColor red(Color::TextColorCode::FG_RED);
     * const Color::TextColor def(Color::TextColorCode::FG_DEFAULT);
     * std::cout << red << "this text has red color"
     *           << def << "this text is default color";
     * @endcode
     */
    class TextColor
    {
    public:
        /**
         * @brief Construct functor according Color::TextColorCode
         * @param[in] colorCode Text color
         */
        TextColor(const Color::TextColorCode& colorCode) noexcept;
        /**
         * @brief Set color code
         * @param[in] colorCode code of color Color::TextColorCode
         */
        void SetCode(const Color::TextColorCode& colorCode) noexcept;
        /**
         * @brief Get color code
         * @return Color code as Color::TextColorCode
         */
        Color::TextColorCode GetCode() const noexcept;
        /**
         * @brief Provides functor functionality
         * @param[out] os Output stream where color code will be written
         * @param[in] mod Text color code
         * @see TextColorCode
         * @return Modified output stream where color code will be written
         */
        friend std::ostream& operator <<(std::ostream& os,
                                         const Color::TextColor& mod) noexcept
        {
           /**
             * "\033[" Is the beginning of the escape
             * sequence for ANSI color codes
            */
           /**
             * "m" is the end of the escape
             * sequence for ANSI color codes
             */
           return os << "\033["
                     << mod._code
                     << "m";
        }

    private:
        /// @brief Text color code
        /// @see TextColorCode
        Color::TextColorCode _code;
    };
}

#endif  /* TEXTCOLOR_H */
