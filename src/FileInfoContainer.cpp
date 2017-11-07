#include "FileInfoContainer.h"

FileInfoContainer::FileInfoContainer() noexcept
{

}

void FileInfoContainer::Add(const FileInfo& value) noexcept
{
    _map.insert(std::make_pair(value.GetSize(), value));
}

void FileInfoContainer::Remove(const FileInfo& value) noexcept
{
    _map.erase(value.GetSize());
}

void FileInfoContainer::Remove(const size_t& key) noexcept
{
    _map.erase(key);
}

void FileInfoContainer::Clear() noexcept
{
    _map.clear();
}

std::multimap<size_t, FileInfo> FileInfoContainer::GetData() const noexcept
{
    return _map;
}
