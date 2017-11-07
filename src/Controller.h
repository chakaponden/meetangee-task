/**
 * @file Controller.h
 * @brief A simple facade for task steps combine
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <stdexcept>

#include "FileInfoContainer.h"

/**
 * @brief Main facade class provides full task functionality
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 8 November 2017
 * @copyright MIT License
 * @details Algorhitm steps:
 *          - download HTML file by HTMLFileURL
 *          - parse HTML file for file link references
 *          - normalize all result raw files link references to absolute URL
 *          - download all parsed files link references by
 *            absolute URL in parallel
 *          - generate adler32 hash for each downloaded file content
 *          - return result file info container
 */
class Controller
{
public:
    /**
     * @brief Default constructor
     */
    Controller() noexcept;
    /**
     * @brief Construct object and set source HTML file absolute URL
     * @param HTMLFileURL Absolute source HTML file URL
     */
    Controller(const std::string& HTMLFileURL) noexcept;
    /**
     * @brief Set source HTML file absolute URL
     * @param value Absolute source HTML file URL
     */
    void SetHTMLFileURL(const std::string& value) noexcept;
    /**
     * @brief Get source HTML file absolute URL
     * @return Absolute source HTML file URL
     */
    std::string GetHTMLFileURL() const noexcept;
    /**
     * @brief Execute main algorhitm full task functionality
     * @details Algorhitm steps:
     *          - download HTML file by HTMLFileURL
     *          - parse HTML file for file link references
     *          - normalize all result raw files link references to absolute URL
     *          - download all parsed files link references by
     *            absolute URL in parallel
     *          - generate adler32 hash for each downloaded file content
     *          - return result file info container
     * @return Container with infomation about every downloaded file in parallel
     */
    FileInfoContainerShp Execute() throw (std::runtime_error, std::invalid_argument);

    /**
     * @brief Get result after Execute() call
     * @return Requested infomation about every downloaded file in parallel
     */
    FileInfoContainerShp GetResult() const;

private:
    std::string _HTMLFileURL;       ///< Absolute source HTML file URL
    /**
     * @brief _result Infomation about every downloaded file in parallel
     */
    FileInfoContainerShp _result;
};

#endif // CONTROLLER_H
