/**
 * DownloaderParallel.h
 *
 * A simple C++ wrapper for the libcurl multiple API.
 * Parallel curl handles execution
 * using synchronous I/O multiplexing: select() call. 
 */
#ifndef DOWNLOADERPARALLEL_H
#define DOWNLOADERPARALLEL_H
#include <string>
#include <vector>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"

/**
 * A threadsafe simple libcURL-multi based downloader:
 * execute all CURL* handles from ICurlEasyDownloader
 * using synchronous I/O multiplexing: select() call.
 */
class DownloaderParallel
{
public:
    DownloaderParallel();
    ~DownloaderParallel();

    void AddDownloader(const ICurlEasyDownloader* downloader);
    void RemoveDownloader(const ICurlEasyDownloader* downloader);

    /**
     * Execute all CURL* handles from ICurlEasyDownloader
     * @return The execution result code
     */
    int Download();
    int operator()();

private:
    CURLM* _curlMultiHandle;
};
#endif  /* DOWNLOADERPARALLEL_H */