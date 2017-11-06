/**
 * @file HTMLParser.h
 * @brief A simple wrapper for the Gumbo HTML5 parser easy API
 */

#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <vector>

/**
 * @brief Get all link references from HTML content
 *        using Gumbo HTML5 parser easy API
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details A simple C++ wrapper for the Gumbo HTML5 parser easy API
 * @see Gumbo
 */
class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    /**
     * @brief Parse a HTML content for all link references
     * @param[in] content The HTML content to be parsed
     * @return All raw link references from HTML content
     */
    static std::vector<std::string> Parse(const std::string& content);

    /**
     * @brief Parse a HTML content for all link references
     * @param[in] content The HTML content to be parsed
     * @param[in] rootURL The root item URL from which relative
     *            full path result will be formed
     * @return All absolute link references from HTML content
     */
    static std::vector<std::string> Parse(const std::string& content,
                                          const std::string& rootURL);
};

#endif  /* HTMLPARSER_H */
