#include "FileInfo.h"

FileInfo::FileInfo(const std::string& absoluteURL,
                   const size_t& sizeInBytes,
                   const unsigned long& adler32Hash) noexcept :
    _URL(absoluteURL),
    _size(sizeInBytes),
    _adler32Hash(adler32Hash)
{
}

void FileInfo::SetURL(const std::string& absoluteURL) noexcept
{
    _URL = absoluteURL;
}

std::string FileInfo::GetURL() const noexcept
{
    return _URL;
}

void FileInfo::SetSize(const size_t& bytes) noexcept
{
    _size = bytes;
}

size_t FileInfo::GetSize() const noexcept
{
    return _size;
}

void FileInfo::SetAdler32Hash(const unsigned long& hash) noexcept
{
    _adler32Hash = hash;
}

unsigned long FileInfo::GetAdler32Hash() const noexcept
{
    return _adler32Hash;
}
