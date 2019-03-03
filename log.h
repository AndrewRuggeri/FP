#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>


/**
* @brief log level logging
*
* @param text text to be put to log
*/
#ifdef LOG_INFO_ON
#define LOG_INFO(text) { \
	std::ostringstream stream; \
	stream << text << std::endl; \
	std::cout << stream.str(); \
}
#else
#define LOG_INFO(text) {}
#endif


/**
* @brief error level logging
*
* @param text text to be put to log
*/
#ifdef LOG_ERROR_ON
#define LOG_ERROR(text) { \
	std::ostringstream stream; \
	stream << text << std::endl; \
	std::cout << stream.str(); \
}
#else
#define LOG_ERROR(text) {}
#endif


/**
* @brief warning level logging
*
* @param text text to be put to log
*/
#ifdef LOG_WARNING_ON
#define LOG_WARNING(text) { \
	std::ostringstream stream; \
	stream << text << std::endl; \
	std::cout << stream.str(); \
}
#else
#define LOG_WARNING(text) {}
#endif

/**
* @brief debug level logging
*
* @param text text to be put to log
*/
#ifdef LOG_DEBUG_ON
#define LOG_DEBUG(text) { \
	std::ostringstream stream; \
	stream << text << std::endl; \
	std::cout << stream.str(); \
}
#else
#define LOG_DEBUG(text) {}
#endif


#endif
