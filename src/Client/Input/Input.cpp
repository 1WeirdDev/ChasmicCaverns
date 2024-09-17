#include "pch.h"
#include "Input.h"

#include "Core/Logger.h"
#include "Game.h"

std::array<uint8_t, 400> Input::s_Keys;

void Input::Init(){
    s_Keys.fill(0);
    CORE_INFO("Initialized Input");
}
void Input::Shutdown(){
    CORE_INFO("Shutdown Input");
}
void Input::Update(){

}

void Input::OnKeyEvent(int key, KeyAction action, unsigned char modifiers){
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