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

    static void OnKeyEvent(int key, KeyAction action, unsigned char modifiers);
    static void OnMouseButtonEvent(int button, bool isDown);

    //If the window is lost focus reset all keys to up
    static void OnWindowLostFocus();
private:
    static std::array<uint8_t, 400> s_Keys;
};