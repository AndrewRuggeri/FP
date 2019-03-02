#include <iostream>
#include "log.h"


void logging::error(char* text) {
	std::cout << text << std::endl;
}


/**
* @brief error level logging
*
* @param text text to be put to log
*/
void logging::warning(char* text) {
	std::cout << text << std::endl;
}

void logging::debug(std::stringstream oss) {
	std::cout << oss.str() << std::endl;
}