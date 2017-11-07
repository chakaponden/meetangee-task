/**
 * @file Operations.hpp
 * @brief Public operations that can not be bind to any class
 */

#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include <gumbo.h>
#include <vector>

#include "easygumbo_global.h"
#include "LogicalAnd.hpp"

namespace EasyGumbo
{
    /**
     * @brief Easy use compatator creation template function
     * @param[in] valueLeft Object constructor functors validator left
     * @param[in] valueRight Object constructor functors validator right
     * @return LogicalAnd<> template comparator
     */
    template<typename TypeLeft, typename TypeRight>
    LogicalAnd<TypeLeft, TypeRight> And(const TypeLeft& valueLeft,
                                        const TypeRight& valueRight) noexcept
    {
        return LogicalAnd<TypeLeft, TypeRight>(valueLeft, valueRight);
    }

    /**
     * @brief Get all nodes by one call - when you do not want to loop by find_if()
     * @param[in] begin Begin iterator for start search point
     * @param[in] end End iterator for end search
     * @param[in] predicate A callable that returns a value testable as a bool
     *                      indicates when something is finded and search need
     *                      to be finished
     * @return Vector of all finded nodes that suits predicate
     */
    template<typename Iterator, typename UnaryPredicate>
    std::vector<GumboNode*> FindAll(Iterator begin, Iterator end,
                                    UnaryPredicate predicate) noexcept
    {
        std::vector<GumboNode*> container;
        for(Iterator i(begin); i != end; ++i)
        {
            if(predicate(*i))
            {
                container.push_back(&(*i));
            }
        }
        return container;
    }
}

#endif // OPERATIONS_HPP
