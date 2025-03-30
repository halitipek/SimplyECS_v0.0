/**
* @file Debug.hpp
 * @brief Debugging and assertion utilities.
 *
 * This file provides helper functions for consistent error detection
 * and reporting within the ECS framework. Designed to have zero cost
 * in release builds.
 */
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <cassert>
#include <cstdio>
#include <iostream>
#include <typeinfo>

namespace ecs {
    /**
     * @brief Debugging and error reporting utilities.
     */
    namespace Debug {
        /**
         * @brief Checks a condition and displays detailed error message if it fails.
         *
         * This function is completely eliminated in release builds with no
         * performance cost. In debug mode, it generates detailed error messages
         * with printf-style string formatting.
         *
         * @tparam Args Parameter types for the format string.
         * @param condition The condition to verify (true means success).
         * @param format Printf-style format string.
         * @param args Parameters to be passed to the format string.
         */
        template<typename... Args>
        inline void Assert(bool condition, const char* format, Args... args) {
#ifndef NDEBUG
            if (!condition) {
                char buffer[1024];
                snprintf(buffer, sizeof(buffer), format, args...);
                std::cerr << "ECS Assertion Failed: " << buffer << std::endl;
                assert(false);
            }
#endif
        }
    } // namespace Debug
} // namespace ecs

#endif // DEBUG_HPP