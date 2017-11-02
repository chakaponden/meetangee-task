/**
 * DownloaderFile.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 */
#include "DownloaderFile.h"
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

DownloaderFile::DownloaderFile()
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
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEFUNCTION, &DownloaderFile::WriteDataFile);
    }
}

DownloaderFile::~DownloaderFile()
{
    if(_curlEasyHandle)
    {
        curl_easy_cleanup(_curlEasyHandle);
    }
}

void DownloaderFile::SetURL(const std::string& URL)
{
    _URL = URL;
}

std::string DownloaderFile::GetURL() const
{
    return _URL;
}

void DownloaderFile::SetFilePath(const std::string& fullPath)
{
    _filePath = fullPath;
}

std::string DownloaderFile::GetFilePath() const
{
    return _filePath;
}

int DownloaderFile::Download()
{
    if(_curlEasyHandle)
    {
        FILE *fp;
        fp = fopen(_filePath.c_str(), "wb");
        if(fp == NULL)
        {
            fprintf(stderr, "fopen() failed: %s\n",
                    strerror(errno));
            return 4;
        }
        curl_easy_setopt(_curlEasyHandle, CURLOPT_URL, _URL.c_str());
        /* control what data CURLOPT_WRITEFUNCTION gets */
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEDATA, fp);
        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(_curlEasyHandle);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return 1;
        }
        if(fclose(fp) == EOF)
        {
            fprintf(stderr, "fclose() failed: %s\n",
                    strerror(errno));
            return 3;
        }
    }
    else
    {
        fprintf(stderr, "curl is not initialized\n");
        return 2;
    }
    return 0;
}

int DownloaderFile::operator()()
{
    return Download();
}

size_t DownloaderFile::WriteDataFile(void* ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}