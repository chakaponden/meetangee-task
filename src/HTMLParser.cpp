/**
 * @file HTMLParser.cpp
 * @brief A simple wrapper for the Gumbo HTML5 parser easy API implementation
 */

#include "URI.h"
#include <sstream>
#include <iostream>
#include <algorithm>

#include "HTMLParser.h"

// EasyGumbo lib source files
#include "Gumbo.h"
#include "DFSIterator.h"
#include "Tag.h"
#include "Element.h"
#include "HasAttribute.h"
#include "Operations.hpp"

HTMLParser::HTMLParser() noexcept
{
}

HTMLParser::~HTMLParser() noexcept
{
}

std::vector<std::string> HTMLParser::Parse(const std::string& content) noexcept
{
    const char* attribute = "href";
    std::vector<std::string> fileRawReferences;
    EasyGumbo::Gumbo parser(content.c_str());
    EasyGumbo::DFSIterator iter = parser.Begin();
    // loop for each Dom node EasyGumbo::Element with link
    while((iter =
           std::find_if(iter, parser.End(),
                        EasyGumbo::And(
                            EasyGumbo::Tag(GUMBO_TAG_LINK),
                            EasyGumbo::HasAttribute(attribute)))) != parser.End())
    {
        // save every link value
        EasyGumbo::Element node(*iter++);
        fileRawReferences.push_back(std::string(node.Attribute(attribute)->value));
    }
    return fileRawReferences;
}

std::vector<std::string> HTMLParser::Parse(const std::string& content,
                                           const std::string& rootURL) noexcept
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
