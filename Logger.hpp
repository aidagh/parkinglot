


#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include "Configuration.hpp"

class Logger
{
    private:
	  Configuration _configuration;
      static std::ostream * throwaway;

	public:
	  static std::ostream * trace;
      static std::ostream * debug;
      static std::ostream * info;
	  
      
      void Initialize();
	  void ShowAll();
	  void ShowInfo();
      void ShowDebug();
	  void ShowNone();
};

std::ostream * Logger::trace = &std::cout;
std::ostream * Logger::debug = &std::cout;
std::ostream * Logger::info = &std::cout;
std::ostream * Logger::throwaway = NULL;

#endif