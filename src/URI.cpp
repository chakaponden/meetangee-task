/**
 * @file URI.cpp
 * @brief A simple data wrapper for the soup lib easy API implementation
 */

#include "URI.h"

URI::URI() :
    _soup(nullptr)
{
}

URI::URI(const URI& base,
         const std::string& relative) : URI::URI()
{
    SetURL(base, relative);
}

URI::URI(const std::string& absolute) : URI::URI()
{
    SetURL(absolute);
}

URI::~URI()
{
    if(_soup)
    {
        soup_uri_free(_soup);
    }
}

void URI::SetURL(const URI& base,
                  const std::string& relative)
{
    if(_soup)
    {
        soup_uri_free(_soup);
    }
    SoupURI* baseSoup = base.GetSoup();
    baseSoup ?
        _soup = soup_uri_new_with_base(baseSoup, relative.c_str()) :
        _soup = nullptr;
}

void URI::SetURL(const std::string& value)
{
    if(_soup)
    {
        soup_uri_free(_soup);
    }
    _soup = soup_uri_new(value.c_str());
}

std::string URI::GetURL() const
{
    if(SOUP_URI_IS_VALID(_soup))
    {
        char* charURL = soup_uri_to_string(_soup, false);
        std::string stringURL(charURL);
        g_free(charURL);
        return stringURL;
    }
    return std::string();
}

void URI::SetScheme(const std::string& value)
{
    if(_soup)
    {
        soup_uri_set_scheme(_soup, value.c_str());
    }
}

std::string URI::GetScheme() const
{
    if(SOUP_URI_IS_VALID(_soup))
    {
        char* charScheme = const_cast<char*>(soup_uri_get_scheme(_soup));
        std::string stringScheme(charScheme);
        g_free(charScheme);
        return stringScheme;
    }
    return std::string();
}

void URI::SetHost(const std::string& value)
{
    if(_soup)
    {
        soup_uri_set_host(_soup, value.c_str());
    }
}

std::string URI::GetHost() const
{
    if(SOUP_URI_IS_VALID(_soup))
    {
        char* charHost = const_cast<char*>(soup_uri_get_host(_soup));
        std::string stringHost(charHost);
        g_free(charHost);
        return stringHost;
    }
    return std::string();
}

bool URI::IsValid() const
{
    return SOUP_URI_IS_VALID(_soup);
}

SoupURI* URI::GetSoup() const
{
    return _soup;
}
