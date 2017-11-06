/**
 * @file DownloaderString.h
 * @brief A simple file content downloader as std::string
 */

#ifndef DOWNLOADERSTRING_H
#define DOWNLOADERSTRING_H

#include <string>
#include <memory>
#include <curl/curl.h>

#include "ICurlEasyDownloader.h"

/**
 * @brief Download file content as std::string using libcurl easy API
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details A non-threadsafe simple libcURL-easy downloader:
 *          downloaded file content accessible by GetContent()
 */
class DownloaderString : public ICurlEasyDownloader
{
    friend class DownloaderParallel;
public:
    DownloaderString();
    ~DownloaderString();
    /**
     * @brief Set source file URL link address for download
     * @param[in] URL source file URL link address
     */
    void SetURL(const std::string& URL);
    /**
     * @brief Get source file URL link address for download
     * @return source file URL link address
     */
    std::string GetURL() const;
    /**
     * @brief Get downloaded file content as std::string
     * @return downloaded file content
     */
    std::string GetContent() const;
    /**
     * @brief Execute download process
     * @return The download execution result code
     * @return 0    Successfully did nothing
     * @return 1    curl_easy_perform() failed
     * @return 2    curl easy is not initialized
     */
    int Download();
    /**
     * @brief Same as Download()
     */
    int operator()();

private:
    /**
     * @brief Curl handler pass data function to std::string
     * @details This callback function gets called by libcurl as soon as
     *          there is data received that needs to be saved
     * @param[in] buffer Points to the delivered data
     * @param[in] size Size of the delivered data in bytes
     * @param[in] nmemb Size multiplier (depends on data type)
     * @param[out] userp Buffer where data will be written
     * @return Written data size in bytes
     */
    static size_t WriteData(void* buffer, size_t size,
                            size_t nmemb, std::string* userp);
    /**
     * @brief Get libcURL-easy API object-provider download process
     * @return libcURL-easy API object pointer
     */
    CURL* GetCurlEasyHandler() const override;

private:
    CURL* _curlEasyHandle;  ///< libcURL-easy API object pointer
    std::string _URL;       ///< Source file URL link address
    std::string _content;   ///< Downloaded file content
};
using DownloaderStringShp = std::shared_ptr<DownloaderString>;

#endif  /* DOWNLOADERSTRING_H */
