#pragma once

#include "pch.h"

class Mathf{
public:
    template <typename T>
    static T Clamp(T val, T min, T max){
        if(val < min)return min;
        if(val > max)return max;
        return val;
    }

    static float ToRadians(float value){
        return value * ((float)M_PI / 180.0f);
    }
};