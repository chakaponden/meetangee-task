/**
 * DownloaderString.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 */
#include "DownloaderString.h"
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

DownloaderString::DownloaderString()
{
    if(!(_curlEasyHandle = curl_easy_init()))
    {
        fprintf(stderr, "curl_easy_init() failed\n");
    }
    else
    {
        /* Tell libcurl to follow HTTP 3xx redirection:
         * header can specify a relative or an absolute URL to follow */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_FOLLOWLOCATION, 1L);
        /* Prevent "longjmp causes uninitialized stack frame" bug:
         * skip all signal handling (can be SIGPIPE or SIGCHLD) */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_NOSIGNAL, 1);
        /* enables automatic decompression of HTTP:
         * requests the server to compress its response using the zlib algorithm */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_ACCEPT_ENCODING, "deflate");
        /* tell libcurl to pass all data to this function */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEFUNCTION, &DownloaderString::WriteData);
        /* control what data CURLOPT_WRITEFUNCTION gets */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEDATA, &_content);
    }
}

DownloaderString::~DownloaderString()
{
    if(_curlEasyHandle)
    {
        curl_easy_cleanup(_curlEasyHandle);
    }
}

void DownloaderString::SetURL(const std::string& URL)
{
    _URL = URL;
}

std::string DownloaderString::GetURL() const
{
    return _URL;
}

std::string DownloaderString::GetContent() const
{
    return _content;
}

int DownloaderString::Download()
{
    _content.clear();
    if(_curlEasyHandle)
    {
        curl_easy_setopt(_curlEasyHandle, CURLOPT_URL, _URL.c_str());
        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(_curlEasyHandle);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "curl is not initialized\n");
        return 2;
    }
    return 0;
}

int DownloaderString::operator()()
{
    return Download();
}

size_t DownloaderString::WriteData(void* buffer, size_t size, size_t nmemb, std::string* userp)
{
    userp->append(static_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}