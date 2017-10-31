/**
 * HTMLParser.h
 *
 * A simple C++ wrapper for the Gumbo HTML5 parser easy API.
 */
#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include <string>
#include <vector>
/**
 * A simple Gumbo HTML5 parser
 */
class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    /**
     * Parse a HTML structure store in a std::string using Gumbo HTML5 parser
     * @param content The HTML content
     * @return The raw parse result: vector of raw parsed content
     */
    std::vector<std::string> Parse(const std::string& content);

    /**
     * Parse a HTML structure store in a std::string using Gumbo HTML5 parser
     * @param content The HTML content
     * @param rootURL The root item URL from which relative full path result will be formed
     * @param content The HTML content
     * @param schemeURL The root item URL scheme
     * @return The full path parse result: vector of parsed content full path
     */
    std::vector<std::string> Parse(const std::string& content,
                                   const std::string& rootURL,
                                   const std::string& schemeURL);
};
#endif  /* HTMLPARSER_H */