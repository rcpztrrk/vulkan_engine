#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace VE {
    class Logger {
    public:
        static void Init();
        
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

// Core log macros
#define VE_CORE_TRACE(...)    ::VE::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VE_CORE_INFO(...)     ::VE::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VE_CORE_WARN(...)     ::VE::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VE_CORE_ERROR(...)    ::VE::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VE_CORE_CRITICAL(...) ::VE::Logger::GetCoreLogger()->critical(__VA_ARGS__)
