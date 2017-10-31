/**
 * HTTPDownloader.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */
#include "HTTPDownloader.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

size_t write_data_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

HTTPDownloader::HTTPDownloader()
{
    _curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader()
{
    curl_easy_cleanup(_curl);
}

std::string HTTPDownloader::Download(const std::string& url)
{
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    /* Tell libcurl to follow redirection */
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    /* Prevent "longjmp causes uninitialized stack frame" bug */
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::string out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    return out;
}

int HTTPDownloader::Download(const std::string& url, const std::string& outputFileName)
{
    FILE *fp;
    fp = fopen(outputFileName.c_str(), "wb");
    if(fp == NULL)
    {
        fprintf(stderr, "fopen() failed: %s\n",
                strerror(errno));
        return 1;
    }
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data_file);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    if(fclose(fp) == EOF)
    {
        fprintf(stderr, "fclose() failed: %s\n",
                strerror(errno));
        return 2;
    }
    return 0;
}