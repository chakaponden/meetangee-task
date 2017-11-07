/**
 * @file Vector.hpp
 * @brief A simple wrapper upon GumboVector
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <gumbo.h>
#include <cassert>

#include "easygumbo_global.h"

namespace EasyGumbo
{
    /**
     * @brief Template wrapper for GumboVector provides indexing functionality
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     */
    template<typename value_type>
    class Vector
    {
    public:
        /**
         * @brief Construct object from reference to raw GumboVector object
         * @param[in] vector Reference to raw GumboVector object
         */
        Vector(GumboVector& vector) noexcept : _vector(vector){}
        /**
         * @brief Get element by index
         * @param index Index of requestable element
         * @return Requestable element from current vector
         */
        value_type operator[](const size_t index) const noexcept
        {
            assert(index < _vector.length);
            return  static_cast<value_type>(_vector.data[index]);
        }
        /**
         * @brief Number of elements currently in the vector
         * @return Elements number in vector
         */
        size_t Size() const noexcept { return _vector.length; }

    private:
        GumboVector& _vector;   ///< Reference to raw GumboVector object
    };
}

#endif // VECTOR_HPP
