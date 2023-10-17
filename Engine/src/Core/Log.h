#pragma once

#include <memory>

#include "Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Kaydee
{
    class Log
    {
        public:
            static void init();
            
            inline static std::shared_ptr<spdlog::logger>& getCoreLogger()
            {
                return s_coreLogger;
            }

            inline static std::shared_ptr<spdlog::logger>& getClientLogger()
            {
                return s_coreLogger;
            }

        private:
            static std::shared_ptr<spdlog::logger> s_coreLogger;
            static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
}

#define KD_CORE_TRACE(...) ::Kaydee::Log::getCoreLogger()->trace(__VA_ARGS__)
#define KD_CORE_INFO(...)  ::Kaydee::Log::getCoreLogger()->info(__VA_ARGS__)
#define KD_CORE_WARN(...)  ::Kaydee::Log::getCoreLogger()->warn(__VA_ARGS__)
#define KD_CORE_ERROR(...) ::Kaydee::Log::getCoreLogger()->error(__VA_ARGS__)
#define KD_CORE_FATAL(...) ::Kaydee::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define KD_TRACE(...)      ::Kaydee::Log::getClientLogger()->trace(__VA_ARGS__)
#define KD_INFO(...)       ::Kaydee::Log::getClientLogger()->info(__VA_ARGS__)
#define KD_WARN(...)       ::Kaydee::Log::getClientLogger()->warn(__VA_ARGS__)
#define KD_ERROR(...)      ::Kaydee::Log::getClientLogger()->error(__VA_ARGS__)
#define KD_FATAL(...)      ::Kaydee::Log::getClientLogger()->fatal(__VA_ARGS__)
