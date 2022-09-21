#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace CBT {

	class CBTE_API Log
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


//Core log macros
#define CBT_CORE_ERROR(...) ::CBT::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CBT_CORE_FATAL(...) ::CBT::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define CBT_CORE_WARN(...) ::CBT::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CBT_CORE_INFO(...) ::CBT::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CBT_CORE_TRACE(...) ::CBT::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define CBT_ERROR(...) ::CBT::Log::GetClientLogger()->error(__VA_ARGS__)
#define CBT_FATAL(...) ::CBT::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define CBT_WARN(...) ::CBT::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CBT_INFO(...) ::CBT::Log::GetClientLogger()->info(__VA_ARGS__)
#define CBT_TRACE(...) ::CBT::Log::GetClientLogger()->trace(__VA_ARGS__)