#include "pch.h"

#include "Time.h"
#include "Core/Logger.h"

std::chrono::high_resolution_clock::time_point Time::s_FrameStart;
std::chrono::high_resolution_clock::time_point Time::s_LastFrameStart;
double Time::s_DeltaTime;

void Time::Init(){
    s_FrameStart = std::chrono::steady_clock::now();
    s_LastFrameStart = std::chrono::steady_clock::now();
    s_DeltaTime = 0.0001f;
}

void Time::Update(){
    s_FrameStart = std::chrono::steady_clock::now();
    s_DeltaTime = (float)(s_FrameStart - s_LastFrameStart).count() / 1000000000.0f;
    s_LastFrameStart = s_FrameStart;
}

float Time::GetFrameStartTime(){return s_FrameStart.time_since_epoch().count();}
float Time::GetDeltaTime(){return s_DeltaTime;}