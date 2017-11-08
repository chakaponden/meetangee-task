/**
 * @file ICurlEasyDownloader.h
 * @brief An interface for simple C++ wrapper for the libcurl easy API
 */

#ifndef ICURLEASYDOWNLOADER_H
#define ICURLEASYDOWNLOADER_H

#include <memory>
#include <curl/curl.h>

#include "easycurl_global.h"

namespace EasyCurl
{
    /**
     * @brief An interface for simple C++ wrapper for the libcurl easy API
     * @version 1.0.0
     * @author chakaponden (itransition.com)
     * @date 4 November 2017
     * @copyright MIT License
     * @details Abstract class. Every simple libcURL-based downloader must
     *          implement this interface for can be executed in parallel
     *          using DownloaderParallel
     */
    class ICurlEasyDownloader
    {
    public:
    	virtual ~ICurlEasyDownloader() {}
        /**
         * @brief Get libcURL-easy API object-provider download process
         * @return LibcURL-easy API object pointer
         */
        virtual CURL* GetCurlEasyHandler() const noexcept = 0;
    };
}

#endif  /* ICURLEASYDOWNLOADER_H */
