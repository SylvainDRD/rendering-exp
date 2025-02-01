#include <iostream>

/// Logging macros
#define _LOCATION_INFO " (" << __FILE__ << ", line " << __LINE__ << ")"
#define _NOP      \
    while (false) \
        ;
#define LOG(msg) std::cout << "[LOG]: " << msg << _LOCATION_INFO << std::endl
#define LOG_WARNING(msg) std::cout << "[\033[1;33mWARNING\033[0m]: " << msg << _LOCATION_INFO << std::endl
#define LOG_ERROR(msg) std::cout << "[\033[1;31mERROR\033[0m]: " << msg << _LOCATION_INFO << std::endl

#ifndef NDEBUG
#define LOG_DEBUG(msg) std::cout << "[\033[1;36mDEBUG\033[0m]: " << msg << _LOCATION_INFO << std::endl
#else
#define LOG_DEBUG(msg) _NOP;
#endif

#define NO_CP(Type)                  \
    Type(const Type &type) = delete; \
    Type &operator=(const Type &type) = delete;
#define NO_MV(Type)             \
    Type(Type &&type) = delete; \
    Type &operator=(Type &&type) = delete;
#define NO_CPMV(Type) \
    NO_CP(Type)       \
    NO_MV(Type)

#define ABORT(msg) LOG_ERROR(msg); std::abort();