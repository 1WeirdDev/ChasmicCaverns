#include "pch.h"
#include "Input.h"

#include "Core/Logger.h"
#include "Game.h"
#include "Rendering/Window.h"

std::vector<KeyUpdate> Input::s_KeyUpdates;
std::array<uint8_t, 400> Input::s_Keys;

double Input::s_MousePosX;
double Input::s_MousePosY;
double Input::s_LastMousePosX;
double Input::s_LastMousePosY;
double Input::s_MouseDeltaX;
double Input::s_MouseDeltaY;
float Input::s_MouseNormalizedX;
float Input::s_MouseNormalizedY;

void Input::Init(){
    s_Keys.fill(0);
    s_MousePosX = 0;
    s_MousePosY = 0;
    s_LastMousePosX = 0;
    s_LastMousePosY = 0;
    s_MouseDeltaX = 0;
    s_MouseDeltaY = 0;
    s_MouseNormalizedX = 0;
    s_MouseNormalizedY = 0;
    CORE_INFO("Initialized Input");
}
void Input::Shutdown(){
    CORE_INFO("Shutdown Input");
}
void Input::Update(){
    s_MouseDeltaX = 0;
    s_MouseDeltaY = 0;

    for(size_t i = 0; i < s_KeyUpdates.size(); i++){
        s_Keys[s_KeyUpdates[i].key] = s_KeyUpdates[i].value;
    }

    s_KeyUpdates.resize(0);
}

void Input::OnMouseMoveEvent(double xPos, double yPos){
    s_MousePosX = xPos;
    s_MousePosY = yPos;
    s_MouseDeltaX = s_MousePosX - s_LastMousePosX;
    s_MouseDeltaY = s_MousePosY - s_LastMousePosY;
    s_LastMousePosX = s_MousePosX;
    s_LastMousePosY = s_MousePosY;

    s_MouseNormalizedX = (float)xPos / (float)Window::GetWidth();
    s_MouseNormalizedY = (float)yPos / (float)Window::GetHeight();
}
void Input::OnKeyEvent(int key, KeyAction action, unsigned char modifiers){
    if(key < 0 || key >= s_Keys.size())return;
        s_Keys[key] = 2;
    if(action != Repeat){
        KeyUpdate update;
        update.key = key;
        update.value = action == Release ? 0 : 1;
        s_KeyUpdates.push_back(update);
    }
    Game::OnKeyEvent(key, action, modifiers);
}

void Input::OnMouseButtonEvent(int button, bool isDown){
    Game::OnMouseButtonEvent(button, isDown);
}
void Input::OnWindowLostFocus(){
    for(size_t i = 0; i < s_Keys.size(); i++){
        if(s_Keys[i] > 0){
            Game::OnKeyEvent(i, KeyAction::Release, 0);
            s_Keys[i] = 0;
        }
    }
}
bool Input::IsKeyPressed(uint16_t key) noexcept{
    if(key < 0 || key >= s_Keys.size())return false;
    return s_Keys[key] == 2;
}
bool Input::IskeyDown(uint16_t key) noexcept{
    if(key < 0 || key >= s_Keys.size())return false;
    return s_Keys[key] > 0;
}