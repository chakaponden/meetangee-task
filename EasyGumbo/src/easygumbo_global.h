/**
 * @file easygumbo_global.h
 * @brief EasyGumbo namespace start-end macroses for easy usage
 * @details Define class A in EasyGumbo namespace using start-end macroses
 *          example:
 * @code
 * EASYGUMBO_NS_BEGIN
 * class A
 * {
 *  public:
 *      void foo() const;
 * };
 * EASYGUMBO_NS_END
 * @endcode
 * @warning Not in use now, because doxygen do not generate namespace
 *          if namespace defined as MACROS
 */

#ifndef EASYGUMBO_GLOBAL_H
#define EASYGUMBO_GLOBAL_H

/**
 * @namespace EasyGumbo
 * @brief Namespace provide simple functionality upon libGumbo
 *        for parse HTML5 dom structure content
 */

/// macros define EasyGumbo namespace start section
#define EASYGUMBO_NS_BEGIN namespace EasyGumbo {
/// macros define EasyGumbo namespace end section
#define EASYGUMBO_NS_END }

#endif // EASYGUMBO_GLOBAL_H
