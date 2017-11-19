/**
 * @file DownloaderParallelSelect.cpp
 * @brief A several files parallel downloader implementation
 */

#include "DownloaderParallelSelect.h"

#include <sys/select.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <errno.h>

using EasyCurl::DownloaderParallelSelect;

DownloaderParallelSelect::DownloaderParallelSelect() throw (std::runtime_error)
{
    if(!(_curlMultiHandle = curl_multi_init()))
    {
        throw std::runtime_error("curl_multi_init() failed");
    }
}

DownloaderParallelSelect::~DownloaderParallelSelect() noexcept
{
    if(_curlMultiHandle)
    {
        curl_multi_cleanup(_curlMultiHandle);
    }
}

void DownloaderParallelSelect::AddDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error)
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

void DownloaderParallelSelect::RemoveDownloader(const EasyCurl::ICurlEasyDownloader* downloader) throw (std::runtime_error)
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

void DownloaderParallelSelect::Download() throw (std::runtime_error)
{
    if(_curlMultiHandle)
    {
        /* Keep number of running handles */
        int stillRunning;
        // Fill timeval structure from msec
        auto convertMsecToTimeval = [](const long int& mSec) -> timeval
        {
            timeval time;
            /* set a suitable timeout to play around with */ 
            time.tv_sec = 1;
            time.tv_usec = 0;
            // fill timeval from curlTimeo in msec
            if(mSec >= 0)
            {
                time.tv_sec = mSec / 1000;
                if(time.tv_sec > 1)
                {
                    time.tv_sec = 1;
                }
                else
                {
                    time.tv_usec = (mSec % 1000) * 1000;
                }
            }
            return time;
        };
        do
        {
            int rc;                 // select() return code - ready descriptors count
            CURLMcode mc;           // curl_multi_fdset() return code

            fd_set fdRead;          // descriptors read
            fd_set fdWrite;         // descriptors write
            fd_set fdExcep;         // descriptors exceptions
            int fdMaxNumber = -1;   // the highest descriptor number libcurl set

            long curlTimeo = -1;    // milliseconds

            /* set zero bits for all file descriptors */
            FD_ZERO(&fdRead);
            FD_ZERO(&fdWrite);
            FD_ZERO(&fdExcep);
            /* Perform the request, res will get the return code */
            CURLMcode res = curl_multi_perform(_curlMultiHandle, &stillRunning);
            /* Check for errors */
            if(res != CURLM_OK)
            {
                std::ostringstream outputstream;
                outputstream << "curl_multi_perform() failed: "
                             << curl_multi_strerror(res);
                throw std::runtime_error(outputstream.str());
            }
            /* get value from curl - how long to wait for action before proceeding in msec */
            curl_multi_timeout(_curlMultiHandle, &curlTimeo);
            timeval timeout = convertMsecToTimeval(curlTimeo);
            /* get file descriptors from the transfers */ 
            mc = curl_multi_fdset(_curlMultiHandle, &fdRead, &fdWrite, &fdExcep, &fdMaxNumber);
            if(mc != CURLM_OK)
            {
                break;
            }
            /* On success the value of fdMaxNumber is guaranteed to be >= -1. We call
               select(fdMaxNumber + 1, ...); specially in case of (fdMaxNumber == -1) there are
               no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
               to sleep 100ms, which is the minimum suggested value in the
               curl_multi_fdset() doc. */
            if(fdMaxNumber == -1)
            {
                timeval wait = { 0, 100 * 1000 }; /* 100ms */
                select(0, NULL, NULL, NULL, &wait);
            }
            else
            {
                /* Note that on some platforms 'timeout' may be modified by select().
                 If you need access to the original value save a copy beforehand. */ 
                select(fdMaxNumber + 1, &fdRead, &fdWrite, &fdExcep, &timeout);
            }
        } while(stillRunning);
    }
    else
    {
        throw std::runtime_error("curl multi is not initialized");
    }
}

void DownloaderParallelSelect::operator()() throw (std::runtime_error)
{
    Download();
}
