#include "pch.h"
#include "Logger.h"
#include "Core.h"

#ifdef USE_SPDLOG
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	
    void Logger::Init(){
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt(GAME_NAME);
		s_CoreLogger->set_level(spdlog::level::trace);
    }
#else
    void Logger::Init(){}
#endif