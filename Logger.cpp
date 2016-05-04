//File:         Logger.cpp
//Description: 	Provides logging to the application

#include "Logger.hpp"

void Logger::Initialize()
{
	int logLevel = _configuration.LogLevel;
	if (logLevel == 0)
	{
		ShowAll();		
	}
	else if (logLevel == 1)
	{
		ShowDebug();		
	}
	else if (logLevel == 2)
	{
		ShowInfo();		
	}
	else
	{
		ShowNone();
	}
	
}

//Show all logging messages
void Logger::ShowAll()
{

}

//Show only Info or higher messages
void Logger::ShowInfo()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
	trace = throwaway;
}


//Show only Debug or higher messages
void Logger::ShowDebug()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
	trace = throwaway;
}

//Show no messages
void Logger::ShowNone()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
    info = throwaway;
	trace = throwaway;

}


