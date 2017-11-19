/**
 * @file DownloaderParallel.cpp
 * @brief A several files parallel downloader implementation
 */

#include "DownloaderParallel.h"

#include <sys/select.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <errno.h>

using EasyCurl::DownloaderParallel;

DownloaderParallel::DownloaderParallel() throw (std::runtime_error)
{
    if(!(_curlMultiHandle = curl_multi_init()))
    {
        throw std::runtime_error("curl_multi_init() failed");
    }
}

DownloaderParallel::~DownloaderParallel() noexcept
{
    if(_curlMultiHandle)
    {
        curl_multi_cleanup(_curlMultiHandle);
    }
}

void DownloaderParallel::AddDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error)
{
    if(_curlMultiHandle)
    {
        curl_multi_add_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
    }
    else
    {
        throw std::runtime_error("curl multi is not initialized");
    }
}

void DownloaderParallel::RemoveDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error)
{
    if(_curlMultiHandle)
    {
        curl_multi_remove_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
    }
    else
    {
        throw std::runtime_error("curl multi is not initialized");
    }
}

void DownloaderParallel::Download() throw (std::runtime_error)
{
    if(_curlMultiHandle)
    {
        /* Keep number of running handles */
        int stillRunning;
        int repeats = 0;
        do
        {
            int fdsNumber;

            CURLMcode res = curl_multi_perform(_curlMultiHandle, &stillRunning);
            if(res != CURLM_OK)
            {
                std::ostringstream outputstream;
                outputstream << "curl_multi_perform() failed: "
                             << curl_multi_strerror(res);
                throw std::runtime_error(outputstream.str());
            }
            else
            {
                /* wait for activity, timeout or "nothing" */
                res = curl_multi_wait(_curlMultiHandle, NULL, 0, 1000, &fdsNumber);
                if(res != CURLM_OK)
                {
                    break;
                }
            }

            /* 'fdsNumber' being zero means either a timeout or no file descriptors to
             wait for. Try timeout on first occurrence, then assume no file
             descriptors and no file descriptors to wait for means wait for 100
             milliseconds. */
            if(!fdsNumber)
            {
                repeats++; /* count number of repeated zero fdsNumber */
                if(repeats > 1)
                {
                    timeval wait = { 0, 100 * 1000 }; /* 100ms */
                    select(0, NULL, NULL, NULL, &wait);
                }
            }
            else
            {
                repeats = 0;
            }
        } while(stillRunning);
    }
    else
    {
        throw std::runtime_error("curl multi is not initialized");
    }
}

void DownloaderParallel::operator()() throw (std::runtime_error)
{
    Download();
}
