/**
 * DownloaderString.h
 *
 * A simple C++ wrapper for the soup lib easy API.
 */
#ifndef SOUPWRAPPER_H
#define SOUPWRAPPER_H
#include <string>


class DownloaderString
{
public:
    DownloaderString();
    ~DownloaderString();

    void SetURL(const std::string& URL);
    std::string GetURL() const;

    std::string GetContent() const;

    /**
     * Download a file using HTTP GET and store in in a std::string
     * @return The download result
     */
    int Download();
    int operator()();

private:
};
#endif  /* SOUPWRAPPER_H */