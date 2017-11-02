/**
 * DownloaderParallel.cpp
 *
 * A simple C++ wrapper for the libcurl multiple API.
 */
#include "DownloaderParallel.h"
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

void DownloaderParallel::AddDownloader(const std::vector<ICurlEasyDownloaderShp>& downloaders)
{
    for(ICurlEasyDownloaderShp downloader : downloaders)
    {
        curl_multi_add_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
    }
}

void DownloaderParallel::RemoveDownloader(const std::vector<ICurlEasyDownloaderShp>& downloaders)
{
    for(ICurlEasyDownloaderShp downloader : downloaders)
    {
        curl_multi_remove_handle(_curlMultiHandle, downloader->GetCurlEasyHandler());
    }
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

    //   do {
    //     struct timeval timeout;
    //     int rc; /* select() return code */ 
    //     CURLMcode mc; /* curl_multi_fdset() return code */ 
     
    //     fd_set fdread;
    //     fd_set fdwrite;
    //     fd_set fdexcep;
    //     int maxfd = -1;
     
    //     long curl_timeo = -1;
     
    //     FD_ZERO(&fdread);
    //     FD_ZERO(&fdwrite);
    //     FD_ZERO(&fdexcep);
     
    //     /* set a suitable timeout to play around with */ 
    //     timeout.tv_sec = 1;
    //     timeout.tv_usec = 0;
     
    //     curl_multi_timeout(multi_handle, &curl_timeo);
    //     if(curl_timeo >= 0) {
    //       timeout.tv_sec = curl_timeo / 1000;
    //       if(timeout.tv_sec > 1)
    //         timeout.tv_sec = 1;
    //       else
    //         timeout.tv_usec = (curl_timeo % 1000) * 1000;
    //     }
 
    //     /* get file descriptors from the transfers */ 
    //     mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);
     
    //     if(mc != CURLM_OK) {
    //       fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
    //       break;
    //     }
     
    //     /* On success the value of maxfd is guaranteed to be >= -1. We call
    //        select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
    //        no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
    //        to sleep 100ms, which is the minimum suggested value in the
    //        curl_multi_fdset() doc. */ 
     
    //     if(maxfd == -1) {
    // #ifdef _WIN32
    //       Sleep(100);
    //       rc = 0;
    // #else
    //       /* Portable sleep for platforms other than Windows. */ 
    //       struct timeval wait = { 0, 100 * 1000 }; /* 100ms */ 
    //       rc = select(0, NULL, NULL, NULL, &wait);
    // #endif
    //     }
    //     else {
    //       /* Note that on some platforms 'timeout' may be modified by select().
    //          If you need access to the original value save a copy beforehand. */ 
    //       rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
    //     }
     
    //     switch(rc) {
    //     case -1:
    //       /* select error */ 
    //       break;
    //     case 0: /* timeout */ 
    //     default: /* action */ 
    //       curl_multi_perform(multi_handle, &still_running);
    //       break;
    //     }
    //   } while(still_running);
     
    //   /* See how the transfers went */ 
    //   while((msg = curl_multi_info_read(multi_handle, &msgs_left))) {
    //     if(msg->msg == CURLMSG_DONE) {
    //       int idx, found = 0;
     
    //       /* Find out which handle this message is about */ 
    //       for(idx = 0; idx<HANDLECOUNT; idx++) {
    //         found = (msg->easy_handle == handles[idx]);
    //         if(found)
    //           break;
    //       }
     
    //       switch(idx) {
    //       case HTTP_HANDLE:
    //         printf("HTTP transfer completed with status %d\n", msg->data.result);
    //         break;
    //       case FTP_HANDLE:
    //         printf("FTP transfer completed with status %d\n", msg->data.result);
    //         break;
    //       }
    //     }
    //   }
    // }
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