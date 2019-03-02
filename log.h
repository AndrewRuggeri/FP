#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>


/**
* @brief some very basic logging
* 
*/
namespace logging {
    
    /**
    * @brief error level logging
    * 
    * @param text text to be put to log
    */
	void error(char* text);
    
    
    /**
    * @brief error level logging
    * 
    * @param text text to be put to log
    */
	void warning(char* text);
    
	void debug(std::stringstream oss);

};


#endif
