/**
 * HTMLParser.cpp
 *
 * A simple C++ wrapper for the Gumbo HTML5 parser easy API.
 *
 */
#include "HTMLParser.h"
#include "Gumbo.hpp"
#include <boost/network/uri.hpp>
#include <boost/network/uri/uri_io.hpp>
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
    std::vector<std::string> fileRawReferences;
    EasyGumbo::Gumbo parser(content.c_str());
    EasyGumbo::Gumbo::iterator iter = parser.begin();
    // loop for each Dom node EasyGumbo::Element with link
    while((iter =
        std::find_if(iter, parser.end(),
            And(EasyGumbo::Tag(GUMBO_TAG_LINK),
                EasyGumbo::HasAttribute("href")))) != parser.end())
    {
        // save every link value
        EasyGumbo::Element node(*iter++);
        fileRawReferences.push_back(std::string(node.attribute("href")->value));
    }
    return fileRawReferences;
}

std::vector<std::string> HTMLParser::Parse(const std::string& content,
                                           const std::string& rootURL,
                                           const std::string& schemeURL)
{
    auto relativeURLToAbsoluteURL = [&rootURL, &schemeURL](const std::string& rawReference)
    {
        boost::network::uri::uri url;
        url << boost::network::uri::scheme(schemeURL)
            << boost::network::uri::host(rootURL)
            << boost::network::uri::path(rawReference);
        return url.string();    
    };
    std::vector<std::string> fileRawReferences = Parse(content);
    std::vector<std::string> fileFullReferences;
    std::transform(fileRawReferences.begin(), fileRawReferences.end(),
                   std::back_inserter(fileFullReferences),
                   relativeURLToAbsoluteURL);
    return fileFullReferences;
}