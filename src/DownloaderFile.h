/**
 * @file DownloaderFile.h
 * @brief A simple file downloader and on storage saver
 */

#ifndef DOWNLOADERFILE_H
#define DOWNLOADERFILE_H

#include <string>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"

/**
 * @brief Download file using libcurl easy API and save it on storage.
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details A non-threadsafe simple libcURL-easy downloader:
 *          save downloaded file on storage by file path
 */
class DownloaderFile : public ICurlEasyDownloader
{
    friend class DownloaderParallel;
public:
    DownloaderFile();
    ~DownloaderFile();
    /**
     * @brief Set source file URL link address for download
     * @param[in] URL Source file URL link address
     */
    void SetURL(const std::string& URL);
    /**
     * @brief Get source file URL link address for download
     * @return Source file URL link address
     */
    std::string GetURL() const;
    /**
     * @brief Set full file path location on storage
     * @param[in] fullPath Full file path location on storage
     */
    void SetFilePath(const std::string& fullPath);
    /**
     * @brief Get full file path location on storage
     * @return Full file path location on storage
     */
    std::string GetFilePath() const;
    /**
     * @brief Execute download process
     * @return The download execution result code
     * @return 0:   successfully did nothing
     * @return 1:   curl_easy_perform() failed
     * @return 2:   curl easy is not initialized
     * @return 3:   fclose() failed
     * @return 4:   file is not opened
     */
    int Download();
    /**
     * @brief Same as Download()
     */
    int operator()();

private:
    /**
     * @brief Curl handler pass data function to FILE
     * @details This callback function gets called by libcurl as soon as
     *          there is data received that needs to be saved
     * @param[in] buffer Points to the delivered data
     * @param[in] size Size of the delivered data in bytes
     * @param[in] nmemb Size multiplier (depends on data type)
     * @param[out] userp Buffer where data will be written
     * @return Written data size in bytes
     */
    static size_t WriteDataFile(void* ptr, size_t size,
                                size_t nmemb, FILE *stream);
    /**
     * @brief Get libcURL-easy API object-provider download process
     * @return LibcURL-easy API object pointer
     */
    CURL* GetCurlEasyHandler() const override;

private:
    CURL* _curlEasyHandle;      ///< libcURL-easy API object pointer
    std::string _URL;           ///< Source file URL link address
    std::string _filePath;      ///< Full file path location on storage
    FILE* _filePointer;         ///< File pointer
};

#endif  /* DOWNLOADERFILE_H */
