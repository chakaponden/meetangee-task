/**
 * @file DFSIterator.h
 * @brief STL compatible iterator for HTML dom structure lookup
 */

#ifndef DFSITERATOR_H
#define DFSITERATOR_H

#include <gumbo.h>
#include <iterator>

#include "easygumbo_global.h"

namespace EasyGumbo
{
    /**
     * @brief STL compatible iterator for HTML dom structure lookup
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details Provide HTML dom structure depth search
     */
    class DFSIterator: public std::iterator<std::input_iterator_tag, GumboNode>
    {
    public:
        /**
         * @brief Copy constructor
         * @param[in] value Value to copy
         */
        DFSIterator(const DFSIterator& value) noexcept;
        /**
         * @brief Construct DFSIterator from raw GumboNode
         * @param[in] node Raw GumboNode pointer
         */
        explicit DFSIterator(GumboNode* node = nullptr) noexcept;
        /**
         * @brief Make copy new iterator from current iterator
         * @return New copied iterator
         */
        DFSIterator FromCurrent() const noexcept;
        /**
         * @brief Trying to adjust iterator current value
         * @return Operation result status
         * @return true:    success
         * @return false:   fail
         */
        bool GotoAdj() noexcept;
        /**
         * @brief Compare current iterator with other by pointer node
         * @param[in] obj Other DFSIterator iterator
         * @return Operation result status
         * @return true:    different
         * @return false:   equal
         */
        bool operator!=(const DFSIterator& obj) const noexcept;
        /**
         * @brief Compare current iterator with other by pointer node
         * @param[in] obj Other DFSIterator iterator
         * @return Operation result status
         * @return true:    equal
         * @return false:   different
         */
        bool operator==(const DFSIterator& obj) const noexcept;
        /**
         * @brief Go to next HTML dom tree element
         * @return Updated current iterator
         */
        DFSIterator& operator++() noexcept;
        /**
         * @brief Go to next HTML dom tree element
         * @return Updated copy-value current iterator
         * @warning Result do not depends on any function input parameter
         */
        DFSIterator operator++(int) noexcept;
        /**
         * @brief Get pointer to current GumboNode
         * @return Pointer to current GumboNode
         */
        GumboNode* operator->() noexcept;
        /**
         * @brief Get reference to current GumboNode
         * @return Reference to current GumboNode
         */
        GumboNode& operator*() noexcept;

    private:
        /**
         * @brief Pass current iterator to first child node
         * @return Operation result status
         * @return true:    successful
         * @return false:   fail
         */
        bool GotoFirstChildren() noexcept;
        /**
         * @brief Pass current iterator to index of vector children
         * @param[in] vector Children of node where current iterator points to
         * @param[in] index Position of child node in vector, where current iterator
         *            need to be set
         * @return Operation result status
         * @return true:    success
         * @return false:   fail
         */
        bool GotoChildren(const GumboVector& vector, size_t index) noexcept;

    private:
        GumboNode* _nodeStart;      ///< Root node where iterator was initialized
        GumboNode* _nodeCurrent;    ///< Current node whare iterator points now
    };
}

#endif // DFSITERATOR_H
