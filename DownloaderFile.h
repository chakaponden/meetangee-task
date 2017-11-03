/**
 * DownloaderFile.h
 *
 * A simple C++ wrapper for the libcurl easy API.
 */
#ifndef DOWNLOADERFILE_H
#define DOWNLOADERFILE_H
#include <string>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"
/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 * save downloaded file on storage by file path
 */
class DownloaderFile : public ICurlEasyDownloader
{
    friend class DownloaderParallel;
public:
    DownloaderFile();
    ~DownloaderFile();

    void SetURL(const std::string& URL);
    std::string GetURL() const;

    void SetFilePath(const std::string& fullPath);
    std::string GetFilePath() const;

    /**
     * Download a file using HTTP GET and save file to file path
     * @return The download result
     */
    int Download();
    int operator()();
    

private:
    /*
     * curl handler pass data function to FILE
     */
    static size_t WriteDataFile(void* ptr, size_t size,
                                size_t nmemb, FILE *stream);
    CURL* GetCurlEasyHandler() const override;

private:
    CURL* _curlEasyHandle;
    std::string _URL;
    std::string _filePath;
    FILE* _filePointer;
};
#endif  /* DOWNLOADERFILE_H */