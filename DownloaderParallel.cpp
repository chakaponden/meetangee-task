/**
 * DownloaderParallel.cpp
 *
 * A simple C++ wrapper for the libcurl multiple API.
 * Parallel curl handles execution
 * using synchronous I/O multiplexing: select() call. 
 */
#include "DownloaderParallel.h"
/* According to POSIX.1-2001 */
#include <bits/time.h>
#include <sys/select.h>
#include <sys/types.h> 
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

DownloaderParallel::DownloaderParallel()
{
    if(!(_curlMultiHandle = curl_multi_init()))
    {
        fprintf(stderr, "curl_multi_init() failed\n");
    }
}

DownloaderParallel::~DownloaderParallel()
{
    if(_curlMultiHandle)
    {
        curl_multi_cleanup(_curlMultiHandle);
    }
}

void DownloaderParallel::AddDownloader(const ICurlEasyDownloader* downloader)
{
    curl_multi_add_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
}

void DownloaderParallel::RemoveDownloader(const ICurlEasyDownloader* downloader)
{
    curl_multi_remove_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
}

int DownloaderParallel::Download()
{
    if(_curlMultiHandle)
    {
        /* Keep number of running handles */
        int stillRunning;
        /* Perform the request, res will get the return code */
        CURLMcode res = curl_multi_perform(_curlMultiHandle, &stillRunning);
        /* Check for errors */
        if(res != CURLM_OK)
        {
            fprintf(stderr, "curl_multi_perform() failed: %s\n",
                    curl_multi_strerror(res));
            return 1;   
        }
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
            fd_set fdExcep;         // descriptors read
            int fdMaxNumber = -1;   // the highest descriptor number libcurl set

            long curlTimeo = -1;    // milliseconds

            /* set zero bits for all file descriptors */
            FD_ZERO(&fdRead);
            FD_ZERO(&fdWrite);
            FD_ZERO(&fdExcep);

            /* get value from curl - how long to wait for action before proceeding in msec */
            curl_multi_timeout(_curlMultiHandle, &curlTimeo);
            timeval timeout = convertMsecToTimeval(curlTimeo);
            /* get file descriptors from the transfers */ 
            mc = curl_multi_fdset(_curlMultiHandle, &fdRead, &fdWrite, &fdExcep, &fdMaxNumber);

            if(mc != CURLM_OK)
            {
                fprintf(stderr, "curl_multi_fdset() failed, code %s.\n",
                    curl_multi_strerror(mc));
                break;
            }

            /* On success the value of fdMaxNumber is guaranteed to be >= -1. We call
               select(fdMaxNumber + 1, ...); specially in case of (fdMaxNumber == -1) there are
               no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
               to sleep 100ms, which is the minimum suggested value in the
               curl_multi_fdset() doc. */ 

            if(fdMaxNumber == -1)
            {
                #ifdef _WIN32
                    Sleep(100);
                    rc = 0;
                #else
                    /* Portable sleep for platforms other than Windows. */ 
                    timeval wait = { 0, 100 * 1000 }; /* 100ms */ 
                    rc = select(0, NULL, NULL, NULL, &wait);
                #endif
            }
            else
            {
                /* Note that on some platforms 'timeout' may be modified by select().
                 If you need access to the original value save a copy beforehand. */ 
                rc = select(fdMaxNumber + 1, &fdRead, &fdWrite, &fdExcep, &timeout);
            }

            switch(rc)
            {
                case -1:    // select error
                {
                    break;
                }
                case 0:     // timeout
                default:    // action  
                {
                    res = curl_multi_perform(_curlMultiHandle, &stillRunning);
                    /* Check for errors */
                    if(res != CURLM_OK)
                    {
                        fprintf(stderr, "curl_multi_perform() failed: %s\n",
                                curl_multi_strerror(res));
                        return 1;   
                    }
                    break;
                }
            }
        } while(stillRunning);
    }
    else
    {
        fprintf(stderr, "curl multi is not initialized\n");
        return 2;
    }
    return 0;
}

int DownloaderParallel::operator()()
{
    return Download();
}