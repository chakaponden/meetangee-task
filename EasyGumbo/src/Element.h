/**
 * @file Element.h
 * @brief A simple wrapper upon GumboNode
 */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <gumbo.h>

#include "easygumbo_global.h"
#include "Vector.hpp"

namespace EasyGumbo
{
    /**
     * @brief Facade class for GumboNode
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     */
    class Element
    {
    public:
        /**
         * @brief Construct Element from raw GumboNode
         * @param[in] element Raw GumboNode reference
         */
        Element(GumboNode& element) noexcept;
        /**
         * @brief The source position for the start of the start tag
         * @return a character position within the original text
         */
        const GumboSourcePosition& Start() const noexcept;
        /**
         * @brief The source position for the start of the end tag
         * @return a character position within the original text
         */
        const GumboSourcePosition& End() const noexcept;
        /**
         * @brief Given a vector of GumboAttributes,
         *        look up the one with the specified name
         * @param[in] name Attribute name case-insensitive match loockup
         * @return
         */
        const GumboAttribute* Attribute(const char* name) const noexcept;
        /**
         * @brief Get an array of GumboNodes,
         *        containing the children of this element
         * @return The children GumboNodes of this element
         */
        EasyGumbo::Vector<GumboNode*> Children() const noexcept;

    private:
        GumboNode& _node;   ///< Reference to raw Gubmo lib object
    };
}

#endif // ELEMENT_H
