/**
 * @file FileInfo.h
 * @brief Simple data class for combine info about file
 */

#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>

/**
 * @brief Simple data class for combine info about file
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 8 November 2017
 * @copyright MIT License
 */
class FileInfo
{
public:
    /**
     * @brief Construct object with parameters
     * @param absoluteURL Absolute file URL
     * @param sizeInBytes File size in bytes
     * @param adler32Hash Adler32 hash of file content
     */
    FileInfo(const std::string& absoluteURL,
             const size_t& sizeInBytes,
             const unsigned long& adler32Hash) noexcept;
    /**
     * @brief Set Absolute file URL
     * @param absoluteURL Absolute file URL
     */
    void SetURL(const std::string& absoluteURL) noexcept;
    /**
     * @brief Get Absolute file URL
     * @return Absolute file URL
     */
    std::string GetURL() const noexcept;
    /**
     * @brief Set file size in bytes
     * @param bytes File size in bytes
     */
    void SetSize(const size_t& bytes) noexcept;
    /**
     * @brief Get file size in bytes
     * @return File size in bytes
     */
    size_t GetSize() const noexcept;
    /**
     * @brief Set adler32 hash of file content
     * @param hash Adler32 hash of file content
     */
    void SetAdler32Hash(const unsigned long& hash) noexcept;
    /**
     * @brief Get adler32 hash of file content
     * @return Adler32 hash of file content
     */
    unsigned long GetAdler32Hash() const noexcept;

private:
    std::string _URL;           ///< Absolute file URL
    size_t _size;               ///< File size in bytes
    unsigned long _adler32Hash; ///< Adler32 hash of file content
};

#endif // FILEINFO_H
