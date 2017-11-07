/**
 * @file HasAttribute.h
 * @brief A simple OOP wrapper for check attibute existance
 */

#ifndef HASATTRIBUTE_H
#define HASATTRIBUTE_H

#include <string>
#include <gumbo.h>

#include "easygumbo_global.h"

namespace EasyGumbo
{
    /**
     * @brief Simple OOP wrapper for check attibute existance by value and type
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     */
    class HasAttribute
    {
    public:
        /**
         * @brief Construct object by attribute type and value
         * @param type Attribute type
         * @param value Attribute value
         */
        HasAttribute(const std::string& type,
                     const std::string& value = std::string()) noexcept;
        /**
         * @brief Compare current attribute with raw GumboNode object
         * @param[in] node Raw GumboNode object
         * @return Operation result status
         * @return true:    equal
         * @return false:   different
         */
        bool operator()(const GumboNode& node) const noexcept;

    private:
        const std::string _type;    ///< Attribute type
        const std::string _value;   ///< Attribute value
    };
}

#endif // HASATTRIBUTE_H
