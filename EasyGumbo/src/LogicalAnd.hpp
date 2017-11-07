/**
 * @file LogicalAnd.hpp
 * @brief A template comparator for user data and GumboNode
 */

#ifndef LOGICALAND_HPP
#define LOGICALAND_HPP

#include <gumbo.h>

#include "easygumbo_global.h"

namespace EasyGumbo
{
    /**
     * @brief Template comparator for user data and GumboNode
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     */
    template<typename TypeLeft, typename TypeRight>
    class LogicalAnd
    {
    public:
        /**
         * @brief Construct object with valueLeft and valueRight
         * @param[in] valueLeft Element left
         * @param[in] valueRight Element right
         */
        LogicalAnd(const TypeLeft& valueLeft, const TypeRight& valueRight) noexcept :
            _valueLeft(valueLeft), _valueRight(valueRight) {}
        /**
         * @brief Compare initialize _valueLeft and _valueRight with reference to
         *        raw GumboNode object construction functors validation
         * @param[in] node reference to raw GumboNode object
         * @return Operation result status
         * @return true:    equal
         * @return false:   different
         */
        bool operator()(const GumboNode& node) const noexcept
        {
            return _valueLeft(node) && _valueRight(node);
        }

    private:
        /**
         * @brief _valueLeft Object constructor functors validator left
         */
        const TypeLeft _valueLeft;
        /**
         * @brief _valueLeft Object constructor functors validator right
         */
        const TypeRight _valueRight;
    };
}

#endif // LOGICALAND_HPP
