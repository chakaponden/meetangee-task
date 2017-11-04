/**
 * DownloaderString.h
 *
 * An interface for simple C++ wrapper for the libcurl easy API.
 */
#ifndef ICURLEASYDOWNLOADER_H
#define ICURLEASYDOWNLOADER_H
#include <memory>
#include <curl/curl.h>

class ICurlEasyDownloader
{
public:
    virtual CURL* GetCurlEasyHandler() const = 0;
};

#endif  /* ICURLEASYDOWNLOADER_H */