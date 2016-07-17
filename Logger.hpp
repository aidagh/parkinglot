//File:         Logger.hpp
//Description: 	Provides logging to the application
//   Initialize() - used to initialize the logger with configuration options set within the configuration Model.
//   ShowAll(), ShowInfo(), ShowDebug(), ShowNone() - Used to set the level of debugging.
//   *trace, *debug, *info - Used to output logging data


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
      static std::ostream * standard;

      void Initialize();
	  void ShowAll();
	  void ShowStandard();
	  void ShowInfo();
      void ShowDebug();
	  void ShowNone();
};

#endif
