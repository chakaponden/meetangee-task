/**
 * URI.h
 *
 * A simple C++ wrapper for the soup lib easy API.
 */
#ifndef URI_H
#define URI_H
#include <string>
#include <libsoup/soup.h>

class URI
{
public:
    URI();
    URI(const URI& base,
        const std::string& relative);
    URI(const std::string& absolute);
    ~URI();

    void SetURL(const URI& base,
                const std::string& relative);

    void SetURL(const std::string& absolute);
    std::string GetURL() const;

    void SetScheme(const std::string& value);
    std::string GetScheme() const;

    void SetHost(const std::string& value);
    std::string GetHost() const;

    bool IsValid() const;

private:
    SoupURI* GetSoup() const;

private:
    SoupURI* _soup;
};
#endif  /* URI_H */