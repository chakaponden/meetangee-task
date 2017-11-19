/**
 * @file DownloaderString.cpp
 * @brief A simple file content downloader as std::string implementation
 */

#include "DownloaderString.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <curl/easy.h>
#include <curl/curlbuild.h>

using EasyCurl::DownloaderString;

DownloaderString::DownloaderString() throw (std::runtime_error)
{
    if(!(_curlEasyHandle = curl_easy_init()))
    {
        throw std::runtime_error("curl_easy_init() failed");
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

DownloaderString::~DownloaderString() noexcept
{
    if(_curlEasyHandle)
    {
        curl_easy_cleanup(_curlEasyHandle);
    }
}

void DownloaderString::SetURL(const std::string& URL) throw (std::runtime_error)
{
    _URL = URL;
    if(_curlEasyHandle)
    {
        curl_easy_setopt(_curlEasyHandle, CURLOPT_URL, _URL.c_str());
    }
    else
    {
        throw std::runtime_error("curl easy is not initialized");
    }
}

std::string DownloaderString::GetURL() const noexcept
{
    return _URL;
}

std::string DownloaderString::GetContent() const noexcept
{
    return _content;
}

void DownloaderString::Download() throw (std::runtime_error)
{
    _content.clear();
    if(_curlEasyHandle)
    {
        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(_curlEasyHandle);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            std::ostringstream outputstream;
            outputstream << "curl_easy_perform() failed: "
                         << curl_easy_strerror(res);
            throw std::runtime_error(outputstream.str());
        }
    }
    else
    {
        throw std::runtime_error("curl easy is not initialized");
    }
}

void DownloaderString::operator()() throw (std::runtime_error)
{
    Download();
}

size_t DownloaderString::WriteData(void* buffer, size_t size, size_t nmemb, std::string* userp) noexcept
{
    userp->append(static_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

CURL* DownloaderString::GetCurlEasyHandler() const noexcept
{
    return _curlEasyHandle;
}
