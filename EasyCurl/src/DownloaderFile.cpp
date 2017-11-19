/**
 * @file DownloaderFile.cpp
 * @brief A simple file downloader and on storage saver implementation
 */

#include "DownloaderFile.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <errno.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>

using EasyCurl::DownloaderFile;

DownloaderFile::DownloaderFile() throw (std::runtime_error)
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
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEFUNCTION, &DownloaderFile::WriteDataFile);
    }
}

DownloaderFile::~DownloaderFile() noexcept
{
    if(_curlEasyHandle)
    {
        curl_easy_cleanup(_curlEasyHandle);
    }
}

void DownloaderFile::SetURL(const std::string& URL) throw (std::runtime_error)
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

std::string DownloaderFile::GetURL() const noexcept
{
    return _URL;
}

void DownloaderFile::SetFilePath(const std::string& fullPath) throw (std::runtime_error, std::invalid_argument)
{
    _filePath = fullPath;
    /* control what data CURLOPT_WRITEFUNCTION gets */
    _filePointer = fopen(_filePath.c_str(), "wb");
    if(_filePointer == NULL)
    {
        std::ostringstream outputstream;
        outputstream << "fopen() failed: " << strerror(errno);
        throw std::invalid_argument(outputstream.str());
        return;
    }
    if(_curlEasyHandle)
    {
        curl_easy_setopt(_curlEasyHandle, CURLOPT_WRITEDATA, _filePointer);
    }
    else
    {
        throw std::runtime_error("curl easy is not initialized");
    }
}

std::string DownloaderFile::GetFilePath() const noexcept
{
    return _filePath;
}

void DownloaderFile::Download() throw (std::runtime_error)
{
    if(_curlEasyHandle)
    {
        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(_curlEasyHandle);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            std::ostringstream outputstream;
            outputstream << "curl_easy_perform() failed: "
                         << curl_easy_strerror(res);
            throw std::runtime_error(outputstream.str());
        }
        if(fclose(_filePointer) == EOF)
        {
            std::ostringstream outputstream;
            outputstream << "fclose() failed: "
                         << strerror(errno);
            throw std::runtime_error(outputstream.str());
        }
    }
    else if(_filePointer == NULL)
    {
        std::ostringstream outputstream;
        outputstream << "file " << _filePath.c_str()
                     << "is not opened: " << strerror(errno);
        throw std::runtime_error(outputstream.str());
    }
    else
    {
        throw std::runtime_error("curl easy is not initialized");
    }
}

void DownloaderFile::operator()() throw (std::runtime_error)
{
    Download();
}

size_t DownloaderFile::WriteDataFile(void* ptr, size_t size, size_t nmemb, FILE *stream) noexcept
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

CURL* DownloaderFile::GetCurlEasyHandler() const noexcept
{
    return _curlEasyHandle;
}
