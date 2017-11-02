/**
 * DownloaderString.h
 *
 * A simple C++ wrapper for the libcurl easy API.
 */
#ifndef ICURLEASYDOWNLOADER_H
#define ICURLEASYDOWNLOADER_H
#include <memory>
#include <curl/curl.h>
/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 * downloaded file content accessible by DownloaderString::GetContent()
 */
class ICurlEasyDownloader
{
public:
    virtual CURL* GetCurlEasyHandler() const = 0;
};
using ICurlEasyDownloaderShp = std::shared_ptr<ICurlEasyDownloader>;

#endif  /* ICURLEASYDOWNLOADER_H */