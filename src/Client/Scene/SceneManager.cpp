#include "pch.h"

#include "SceneManager.h"

std::vector<Scene*> SceneManager::s_Scenes;

void SceneManager::Init(){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->Init();
    }
}
void SceneManager::Shutdown(){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->CleanUp();
        delete s_Scenes[i];
    }
}

void SceneManager::Update(){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->Update();
    }
}
void SceneManager::Draw(){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->Draw();
    }
}

bool SceneManager::RemoveScene(Scene* scene){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        if(s_Scenes[i] == scene){
            s_Scenes.erase(s_Scenes.begin() + i);
            return true;
        }
    }
    return false;
}

bool SceneManager::DeleteScene(Scene* scene){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        if(s_Scenes[i] == scene){
            s_Scenes[i]->CleanUp();
            delete s_Scenes[i];
            s_Scenes.erase(s_Scenes.begin() + i);
            return true;
        }
    }
    return false;
}

void SceneManager::OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers){
    bool handled = false;
    for(size_t i = 0; i < s_Scenes.size(); i++){
        if(s_Scenes[i]->OnKeyDownEvent(key, action, modifiers, handled))
            handled = true;
    }
}
void SceneManager::OnMouseButtonEvent(int button, bool isDown){
    bool handled = false;
    for(size_t i = 0; i < s_Scenes.size(); i++){
        if(s_Scenes[i]->OnMouseButtonEvent(button, isDown, handled))
            handled = true;
    }
}

void SceneManager::OnWindowResizeEvent(int width, int height){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->OnWindowResizeEvent(width, height);
    }
}