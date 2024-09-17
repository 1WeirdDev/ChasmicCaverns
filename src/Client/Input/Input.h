#pragma once

#include "pch.h"

enum KeyAction{
    Press = 0,
    Repeat,
    Release
};

enum KeyModifierBit{
    None = 0,
    LeftShift = (1 << 0),
    Control = (1 << 1),
};
class Input{
public:
    static void Init();
    static void Shutdown();

    static void Update();

    static void OnMouseMoveEvent(double xPos, double yPos);
    static void OnKeyEvent(int key, KeyAction action, unsigned char modifiers);
    static void OnMouseButtonEvent(int button, bool isDown);

    //If the window is lost focus reset all keys to up
    static void OnWindowLostFocus();

public:
    static double GetMousePosX() noexcept{return s_MousePosX;}
    static double GetMousePosY() noexcept{return s_MousePosY;}
    static double GetLastMousePosX() noexcept{return s_LastMousePosX;}
    static double GetLastMousePosY() noexcept{return s_LastMousePosY;}
    static double GetMouseDeltaX() noexcept{return s_MouseDeltaX;}
    static double GetMouseDeltaY() noexcept{return s_MouseDeltaY;}
    static float GetMouseNormalizedX() noexcept{return s_MouseNormalizedX;}
    static float GetMouseNormalizedY() noexcept{return s_MouseNormalizedY;}
private:
    static std::array<uint8_t, 400> s_Keys;
    static double s_MousePosX;
    static double s_MousePosY;
    static double s_LastMousePosX;
    static double s_LastMousePosY;
    static double s_MouseDeltaX;
    static double s_MouseDeltaY;
    static float s_MouseNormalizedX;
    static float s_MouseNormalizedY;
};