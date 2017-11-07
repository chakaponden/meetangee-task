/**
 * @file Gumbo.h
 * @brief A main simple wrapper upon Gumbo lib
 */

#ifndef GUMBO_H
#define GUMBO_H

#include <gumbo.h>
#include <memory>

#include "easygumbo_global.h"
#include "DFSIterator.h"

namespace EasyGumbo
{
    /**
     * @brief Main wrapper upon Gumbo lib
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details Provide functionality upon Gumbo lib with
     *          STL compatible iterator - DFSIterator.
     *          Parce HTML dom content represented as char buffer to GumboOuput.
     */
    class Gumbo
    {
    public:
        /**
         * @brief Construct object by parse HTML dom structure content
         *        represented as char input buffer
         * @param[in] buffer Pointer to HTML dom structure content
         */
        Gumbo(const char* buffer) noexcept;
        /**
         * @brief Check if parse result is valid
         * @return Parce process result status
         * @return true:    sucess
         * @return false:   fail
         */
        operator bool() const noexcept;
        /**
         * @brief Get begin iterator to parsed HTML dom structure
         * @return Begin iterator to parsed HTML dom structure
         */
        EasyGumbo::DFSIterator Begin() noexcept;
        /**
         * @brief Get end iterator to parsed HTML dom structure
         * @return End iterator to parsed HTML dom structure
         */
        EasyGumbo::DFSIterator End() noexcept;
        /**
         * @brief Get pointer to raw GumboOutput object
         * @return Pointer to raw GumboOutput object
         */
        GumboOutput* Output() const noexcept;

    private:
        /**
         * @brief _output Shared pointer to raw Gumbo lib output object
         *                incapsulate parsed output HTML dom structure
         */
        std::shared_ptr<GumboOutput> _output;
    };
}

#endif // GUMBO_H
