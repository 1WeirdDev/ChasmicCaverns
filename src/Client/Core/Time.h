#pragma once

#include "pch.h"

class Time{
public:
    static void Init();
    static void Update();
    static float GetFrameStartTime();
    static float GetDeltaTime();
private:
    static std::chrono::high_resolution_clock::time_point s_FrameStart;
    static std::chrono::high_resolution_clock::time_point s_LastFrameStart;
    static double s_DeltaTime;
};