/**
 * HTMLParser.cpp
 *
 * A simple C++ wrapper for the Gumbo HTML5 parser easy API.
 *
 */
#include "HTMLParser.h"
#include "Gumbo.hpp"
#include "URI.h"
#include <sstream>
#include <iostream>
#include <algorithm>

HTMLParser::HTMLParser()
{
}

HTMLParser::~HTMLParser()
{
}

std::vector<std::string> HTMLParser::Parse(const std::string& content)
{
    const char* attribute = "href";
    std::vector<std::string> fileRawReferences;
    EasyGumbo::Gumbo parser(content.c_str());
    EasyGumbo::Gumbo::iterator iter = parser.begin();
    // loop for each Dom node EasyGumbo::Element with link
    while((iter =
        std::find_if(iter, parser.end(),
            And(EasyGumbo::Tag(GUMBO_TAG_LINK),
                EasyGumbo::HasAttribute(attribute)))) != parser.end())
    {
        // save every link value
        EasyGumbo::Element node(*iter++);
        fileRawReferences.push_back(std::string(node.attribute(attribute)->value));
    }
    return fileRawReferences;
}

std::vector<std::string> HTMLParser::Parse(const std::string& content,
                                           const std::string& rootURL)
{
    URI rootURI(rootURL);
    // lambda convert relative URL to absolute URL
    // @return The absolute URL
    auto relativeURLToAbsoluteURL = [&rootURI](const std::string& rawReference)
    {
        URI relativeURI(rawReference);
        if(!relativeURI.IsValid())
        {
            relativeURI.SetURL(rootURI, rawReference);
        }
        return relativeURI.GetURL();
    };
    std::vector<std::string> fileRawReferences = Parse(content);
    std::vector<std::string> fileFullReferences;
    // convert relative to absolute references finded in content
    std::transform(fileRawReferences.begin(), fileRawReferences.end(),
                   std::back_inserter(fileFullReferences),
                   relativeURLToAbsoluteURL);
    return fileFullReferences;
}