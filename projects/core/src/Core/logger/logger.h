#pragma once
#include <memory>

#include "spdlog/spdlog.h"

namespace Core {
	class Log
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

#if defined CORE_DEBUG || defined CORE_RELEASE || defined CORE_DEV_ENABLE_LOGS //Debug / Release defs

//Core Errors macros
/* Macro for loggin engine error's */
#define CORE_ERROR(...) ::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
/* Macro for loggin engine warning's */
#define CORE_WARN(...)  ::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
/* Macro for loggin engine info's */
#define CORE_INFO(...)  ::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
/* Macro for loggin engine debug info */
#define CORE_DEBUG_LOG(...) ::Core::Log::GetCoreLogger()->debug(__VA_ARGS__)
/* Macro for loggin engine trace */
#define CORE_TRACE(...) ::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
/* Macro for loggin engine fatal(errors probably) */
#define CORE_FATAL(...) ::Core::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Application Errors macros
/* Macro for loggin application/game error's */
#define APP_ERROR(...) ::Core::Log::GetClientLogger()->error(__VA_ARGS__)
/* Macro for loggin application/game wanning's */
#define APP_WARN(...)  ::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
/* Macro for loggin application/game info's */
#define APP_INFO(...)  ::Core::Log::GetClientLogger()->info(__VA_ARGS__)
/* Macro for loggin application/game debug info */
#define APP_DEBUG(...) ::Core::Log::GetClientLogger()->debug(__VA_ARGS__)
/* Macro for loggin application/game trace */
#define APP_TRACE(...) ::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
/* Macro for loggin application/game fatal(errors probably) */
#define APP_FATAL(...) ::Core::Log::GetClientLogger()->fatal(__VA_ARGS__)

#else //Dist defs

//Core Errors macros
/* Macro for loggin engine error's */
#define CORE_ERROR(...) 
/* Macro for loggin engine warning's */
#define CORE_WARN(...) 
/* Macro for loggin engine info's */
#define CORE_INFO(...) 
/* Macro for loggin engine debug info */
#define CORE_DEBUG_LOG(...) 
/* Macro for loggin engine trace */
#define CORE_TRACE(...) 
/* Macro for loggin engine fatal(errors probably) */
#define CORE_FATAL(...) 

//Application Errors macros
/* Macro for loggin application/game error's */
#define APP_ERROR(...) 
/* Macro for loggin application/game wanning's */
#define APP_WARN(...) 
/* Macro for loggin application/game info's */
#define APP_INFO(...) 
/* Macro for loggin application/game debug info */
#define APP_DEBUG(...) 
/* Macro for loggin application/game trace */
#define APP_TRACE(...) 
/* Macro for loggin application/game fatal(errors probably) */
#define APP_FATAL(...) 

#endif