/**
 * @file FileInfoContainer.h
 * @brief Simple wrapper upon std::multimap FileInfo container objects
 */

#ifndef FILEINFOCONTAINER_H
#define FILEINFOCONTAINER_H

#include <string>
#include <map>
#include <memory>

#include "FileInfo.h"

/**
 * @brief Simple wrapper upon std::multimap FileInfo container objects
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 8 November 2017
 * @copyright MIT License
 */
class FileInfoContainer
{
public:
    /**
     * @brief Default constructor
     */
    FileInfoContainer() noexcept;
    /**
     * @brief Append object to container
     * @param value FileInfo object to append
     */
    void Add(const FileInfo& value) noexcept;
    /**
     * @brief Remove object from container by value
     * @param value FileInfo object to remove
     */
    void Remove(const FileInfo& value) noexcept;
    /**
     * @brief Remove object from container by key
     * @param key Objects key to remove
     */
    void Remove(const size_t& key) noexcept;
    /**
     * @brief Remove all objects from container
     */
    void Clear() noexcept;
    /**
     * @brief Get raw data container
     * @return Multi map raw STL data container
     */
    std::multimap<size_t, FileInfo> GetData() const noexcept;

private:
    /**
     * @brief _map Multi map raw STL data container
     */
    std::multimap<size_t, FileInfo> _map;
};
using FileInfoContainerShp = std::shared_ptr<FileInfoContainer>;

#endif // FILEINFOCONTAINER_H
