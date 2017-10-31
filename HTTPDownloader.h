/**
 * HTTPDownloader.h
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */
#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H
#include <string>
/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 */
class HTTPDownloader
{
public:
    HTTPDownloader();
    ~HTTPDownloader();
    /**
     * Download a file using HTTP GET and store in in a std::string
     * @param url The URL to download
     * @return The download result
     */
    std::string Download(const std::string& url);
    /**
     * Download a file using HTTP GET and save file to outputFileName path
     * @param url The URL file to download
     * @param outputFileName The output file full path
     * @return 0 on success, not 0 on error
     */
    int Download(const std::string& url, const std::string& outputFileName);
private:
    void* _curl;
};
#endif  /* HTTPDOWNLOADER_H */