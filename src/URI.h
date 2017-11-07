/**
 * @file URI.h
 * @brief A simple data wrapper for the soup lib easy API
 */

#ifndef URI_H
#define URI_H

#include <string>
#include <libsoup/soup.h>

/**
 * @brief A simple data wrapper for the soup lib easy API
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details Represents OOP data URI functionality using non-OOP soup lib API
 */
class URI
{
public:
    URI() noexcept;
    /**
     * @brief Construct object based on base root URI address + path
     * @param base Base root URI
     * @param relative Relative path from base root URI
     */
    URI(const URI& base,
        const std::string& relative) noexcept;
    /**
     * @brief Construct object with absolute URI address
     * @param absolute Absolute URI address
     */
    URI(const std::string& absolute) noexcept;
    ~URI() noexcept;
    /**
     * @brief Set URI based on base root URI address + path
     * @param base Base root URI
     * @param relative Relative path from base root URI
     */
    void SetURL(const URI& base,
                const std::string& relative) noexcept;
    /**
     * @brief Set URI with absolute URI address
     * @param absolute Absolute URI address
     */
    void SetURL(const std::string& absolute) noexcept;
    /**
     * @brief Get absolute URI as std::string
     * @return Absolute URI
     */
    std::string GetURL() const noexcept;
    /**
     * @brief Set URI scheme (http://, ftp:// etc.) as std::string
     * @param value URI scheme
     */
    void SetScheme(const std::string& value) noexcept;
    /**
     * @brief Get URI scheme (http://, ftp:// etc.) as std::string
     * @return URI scheme
     */
    std::string GetScheme() const noexcept;
    /**
     * @brief Set URI host as std::string
     * @param value URI host
     */
    void SetHost(const std::string& value) noexcept;
    /**
     * @brief Get URI host as std::string
     * @return URI host
     */
    std::string GetHost() const noexcept;
    /**
     * @brief Check if URI address is valid accodring RFC 3986
     * @return true:    Valid
     * @return false:   Invalid
     */
    bool IsValid() const noexcept;
    /**
     * @brief Check if URI address is valid accodring RFC 3986
     * @param[in] absoluteURL URI absolute address for validation
     * @return true:    Valid
     * @return false:   Invalid
     */
    static bool IsValid(const std::string& absoluteURL) noexcept;

private:
    /**
     * @brief Get soup lib API object-provider URI non-OOP functionality
     * @return Soup lib API object pointer
     */
    SoupURI* GetSoup() const noexcept;

private:
    SoupURI* _soup;     ///< soup lib API object pointer
};

#endif  /* URI_H */
