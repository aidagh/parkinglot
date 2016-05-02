
#include <iostream>

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

class Logger
{
    private:
      static std::ostream * throwaway;

	public:
	  
      static std::ostream * debug;
      static std::ostream * info;
      
//	  std::ostream * Message();
	  void ShowAll();
	  void ShowNone();
	  void ShowInfo();
	  
	  //std::ostream Message();
};

std::ostream * Logger::debug = &std::cout;
std::ostream * Logger::info = &std::cout;
std::ostream * Logger::throwaway = NULL;

//std::ostream Logger::Message()
//{
//	return *message;
//	
//}
#endif