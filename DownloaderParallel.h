/**
 * DownloaderParallel.h
 *
 * A simple C++ wrapper for the libcurl multiple API.
 */
#ifndef DOWNLOADERPARALLEL_H
#define DOWNLOADERPARALLEL_H
#include <string>
#include <vector>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"

/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 * downloaded file content accessible by DownloaderParallel::GetContent()
 */
class DownloaderParallel
{
public:
    DownloaderParallel();
    ~DownloaderParallel();

    void AddDownloader(const std::vector<ICurlEasyDownloaderShp>& downloaders);
    void RemoveDownloader(const std::vector<ICurlEasyDownloaderShp>& downloaders);

    /**
     * Download a file using HTTP GET and store in in a std::string
     * @return The download result
     */
    int Download();
    int operator()();

private:
    CURLM* _curlMultiHandle;
};
#endif  /* DOWNLOADERPARALLEL_H */