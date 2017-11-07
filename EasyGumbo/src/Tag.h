/**
 * @file Tag.h
 * @brief A simple wrapper upon GumboTag
 */

#ifndef TAG_H
#define TAG_H

#include <gumbo.h>

#include "easygumbo_global.h"

namespace EasyGumbo
{
    /**
     * @brief Wrapper for GumboTag provides comparator functionality
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     */
    class Tag
    {
    public:
        /**
         * @brief Construct object from raw GumboTag
         * @param tag Raw GumboTag object
         */
        Tag(GumboTag tag) noexcept;
        /**
         * @brief Compare current tag with raw GumboTag object
         * @param[in] node Raw GumboTag object
         * @return Operation result status
         * @return true:    equal
         * @return false:   different
         */
        bool operator()(const GumboNode& node) const noexcept;

    private:
        const GumboTag _tag;    ///< Raw GumboTag object
    };
}

#endif // TAG_H
