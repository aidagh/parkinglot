
#include "Logger.hpp"

void Logger::ShowAll()
{

}

void Logger::ShowNone()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
    info = throwaway;
}

void Logger::ShowInfo()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
}

