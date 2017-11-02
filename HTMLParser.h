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
 * get all link references from HTML content
 */
class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    /**
     * Parse a HTML structure store in a std::string using Gumbo HTML5 parser
     * @param content The HTML content
     * @return The raw parse result: vector of raw link references from HTML content
     */
    std::vector<std::string> Parse(const std::string& content);

    /**
     * Parse a HTML structure store in a std::string using Gumbo HTML5 parser
     * @param content The HTML content
     * @param rootURL The root item URL from which relative full path result will be formed
     * @return The absolute parse result: vector of absolute link references from HTML content
     */
    std::vector<std::string> Parse(const std::string& content,
                                   const std::string& rootURL);
};
#endif  /* HTMLPARSER_H */