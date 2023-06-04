#pragma once

#include "spdlog/spdlog.h"

namespace Engine
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr <spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr <spdlog::logger> s_CoreLogger;
		static std::shared_ptr <spdlog::logger> s_ClientLogger;
	};

}

#define CORE_TRACE_LOG(...)    Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO_LOG(...)    Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN_LOG(...)    Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR_LOG(...)  Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_ASSERT_LOG(x, ...)    if(!x)Engine::Log::GetCoreLogger()->error(__VA_ARGS__); ASSERT(x);

#define TRACE_LOG(...)        Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define INFO_LOG(...)        Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define WARN_LOG(...)        Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR_LOG(...)        Engine::Log::GetClientLogger()->error(__VA_ARGS__)