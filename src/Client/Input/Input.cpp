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