#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"


namespace Celestial
{
	class CELESTIAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//! Core log Macros
#define CL_CORE_FATAL(...)     ::Celestial::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CL_CORE_ERROR(...)     ::Celestial::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CL_CORE_WARN(...)      ::Celestial::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CL_CORE_INFO(...)      ::Celestial::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CL_CORE_TRACE(...)     ::Celestial::Log::GetCoreLogger()->trace(__VA_ARGS__)

//! Client Log Macros
#define CL_CLIENT_FATAL(...)     ::Celestial::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CL_CLIENT_ERROR(...)     ::Celestial::Log::GetClientLogger()->error(__VA_ARGS__)
#define CL_CLIENT_WARN(...)      ::Celestial::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CL_CLIENT_INFO(...)      ::Celestial::Log::GetClientLogger()->info(__VA_ARGS__)
#define CL_CLIENT_TRACE(...)     ::Celestial::Log::GetClientLogger()->trace(__VA_ARGS__)
