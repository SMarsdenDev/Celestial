/*****************************************************************************/
/*!
\file   Log.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the definition of the Logging system, which is a
		wrapper around spdlog

		Functions include:

			 + Init
*!/
/*****************************************************************************/
#include "clpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Celestial
{

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	/*****************************************************************************/
		/*!
			\brief
				Initializes the log, setting patterns and color configuration
		*/
	/*****************************************************************************/
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("CELESTIAL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}