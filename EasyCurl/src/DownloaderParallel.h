/**
 * @file DownloaderParallel.h
 * @brief A several files parallel downloader
 */

#ifndef DOWNLOADERPARALLEL_H
#define DOWNLOADERPARALLEL_H

#include <string>
#include <vector>
#include <stdexcept>
#include <curl/curl.h>

#include "easycurl_global.h"
#include "ICurlEasyDownloader.h"

namespace EasyCurl
{
    /**
     * @brief Download several files in parallel using libcurl multi API and
     *        curl_multi_wait() call
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details A threadsafe simple libcURL-multi based downloader:
     *          parallel easy curl handles execution
     *          using curl_multi_wait() call
     * @warning All easy curl handles (ICurlEasyDownloader downloaders) data
     *          must by ready and only wait for curl_easy_perform() call
     * @warning Encouraged to be used instead of DownloaderParallelSelect class
     *          because DownloaderParallelSelect has limitation with
     *          1024 maximum downloads at once
     */
    class DownloaderParallel
    {
    public:
        DownloaderParallel() throw (std::runtime_error);
        ~DownloaderParallel() noexcept;

        /**
         * @brief Append ICurlEasyDownloader derivative downloader
         *        to execution queue for parallel downloading
         * @param[in] downloader ICurlEasyDownloader derivative downloader
         */
        void AddDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error);
        /**
         * @brief Remove ICurlEasyDownloader derivative downloader
         *        from execution queue for parallel downloading
         * @param[in] downloader ICurlEasyDownloader derivative downloader
         */
        void RemoveDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error);
        /**
         * @brief Process parallel download for all ICurlEasyDownloader
         *        derivative downloaders in execution queue
         */
        void Download() throw (std::runtime_error);
        /**
         * @brief Same as Download()
         */
        void operator()() throw (std::runtime_error);

    private:
        /// LibcURL multi handle provides parallel execution.
        CURLM* _curlMultiHandle;
    };
}

#endif  /* DOWNLOADERPARALLEL_H */
