/**
 * @file DownloaderParallel.h
 * @brief A several files parallel downloader
 */

#ifndef DOWNLOADERPARALLEL_H
#define DOWNLOADERPARALLEL_H

#include <string>
#include <vector>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"

/**
 * @brief Download several files in parallel using libcurl multi API
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details A threadsafe simple libcURL-multi based downloader:
 *          parallel easy curl handles execution
 *          using synchronous I/O multiplexing: select() call.
 * @warning All easy curl handles (ICurlEasyDownloader downloaders) data
 *          must by ready and only wait for curl_easy_perform() call
 * @todo Implementation with epoll() system call
 */
class DownloaderParallel
{
public:
    DownloaderParallel();
    ~DownloaderParallel();

    /**
     * @brief Append ICurlEasyDownloader derivative downloader
     *        to execution queue for parallel downloading
     * @param[in] downloader ICurlEasyDownloader derivative downloader
     */
    void AddDownloader(const ICurlEasyDownloader* downloader);
    /**
     * @brief Remove ICurlEasyDownloader derivative downloader
     *        from execution queue for parallel downloading
     * @param[in] downloader ICurlEasyDownloader derivative downloader
     */
    void RemoveDownloader(const ICurlEasyDownloader* downloader);
    /**
     * @brief Process parallel download for all ICurlEasyDownloader
     *        derivative downloaders in execution queue
     * @return The download execution result code
     * @return 0:   successfully did nothing
     * @return 1:   curl_multi_perform() failed
     * @return 2:   curl multi is not initialized
     */
    int Download();
    /**
     * @brief Same as Download()
     */
    int operator()();

private:
    /// LibcURL multi handle provides parallel execution.
    CURLM* _curlMultiHandle;
};

#endif  /* DOWNLOADERPARALLEL_H */
