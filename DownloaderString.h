/**
 * DownloaderString.h
 *
 * A simple C++ wrapper for the libcurl easy API.
 */
#ifndef DOWNLOADERSTRING_H
#define DOWNLOADERSTRING_H
#include <string>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"
/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 * downloaded file content accessible by DownloaderString::GetContent()
 */
class DownloaderString : private ICurlEasyDownloader
{
    friend class DownloaderParallel;
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
    /*
     * curl handler pass data function to std::string
     */
    static size_t WriteData(void* buffer, size_t size,
                            size_t nmemb, std::string* userp);
    CURL* GetCurlEasyHandler() const override;

private:
    CURL* _curlEasyHandle;
    std::string _URL;
    std::string _content;
};
#endif  /* DOWNLOADERSTRING_H */