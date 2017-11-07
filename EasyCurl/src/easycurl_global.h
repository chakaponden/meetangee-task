/**
 * @file easycurl_global.h
 * @brief EasyCurl namespace start-end macroses for easy usage
 * @details Define class A in EasyCurl namespace using start-end macroses
 *          example:
 * @code
 * EASYCURL_NS_BEGIN
 * class A
 * {
 *  public:
 *      void foo() const;
 * };
 * EASYCURL_NS_END
 * @endcode
 * @warning Not in use now, because doxygen do not generate namespace
 *          if namespace defined as MACROS
 */

#ifndef EASYCURL_GLOBAL_H
#define EASYCURL_GLOBAL_H

/**
 * @namespace EasyCurl
 * @brief Namespace provide simple functionality libcURL based downloaders
 */

/// macros define EasyCurl namespace start section
#define EASYCURL_NS_BEGIN namespace EasyCurl {
/// macros define EasyCurl namespace end section
#define EASYCURL_NS_END }

#endif // EASYCURL_GLOBAL_H
