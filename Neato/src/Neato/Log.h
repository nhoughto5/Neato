#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace Neato {
    class NEATO_API Log
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

// Core Log Macros
#define NEATO_CORE_ERROR(...)    ::Neato::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NEATO_CORE_WARN(...)     ::Neato::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NEATO_CORE_INFO(...)     ::Neato::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NEATO_CORE_TRACE(...)    ::Neato::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NEATO_CORE_FATAL(...)    ::Neato::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define NEATO_ERROR(...)         ::Neato::Log::GetClientLogger()->error(__VA_ARGS__)
#define NEATO_WARN(...)          ::Neato::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NEATO_INFO(...)          ::Neato::Log::GetClientLogger()->info(__VA_ARGS__)
#define NEATO_TRACE(...)         ::Neato::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NEATO_FATAL(...)         ::Neato::Log::GetClientLogger()->fatal(__VA_ARGS__)