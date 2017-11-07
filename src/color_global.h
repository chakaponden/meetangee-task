/**
 * @file color_global.h
 * @brief Color namespace start-end macroses for easy usage
 * @details Define class A in Color namespace using start-end macroses
 *          example:
 * @code
 * COLOR_NS_BEGIN
 * class A
 * {
 *  public:
 *      void foo() const;
 * };
 * COLOR_NS_END
 * @endcode
 * @warning Not in use now, because doxygen do not generate namespace
 *          if namespace defined as MACROS
 */

#ifndef COLOR_GLOBAL_H
#define COLOR_GLOBAL_H

/**
 * @namespace Color
 * @brief Namespace provide simple functionality
 *        to colorize terminal text by ASCII colors
 */

/// macros define EasyGumbo namespace start section
#define COLOR_NS_BEGIN namespace Color {
/// macros define EasyGumbo namespace end section
#define COLOR_NS_END }

#endif // COLOR_GLOBAL_H
