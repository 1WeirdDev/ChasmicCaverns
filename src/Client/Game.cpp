#include "pch.h"

#include "Game.h"
#include "Math/MatrixUtils.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes/MainMenuScene.h"
#include "Rendering/Gui/UIDisplayManager.h"
#include "Core/Mathf.h"

Player Game::player;
Cave Game::cave;
Mat4x4 Game::s_ProjMatrix;
BasicMesh Game::s_BasicMesh;

int Game::s_ProjMatrixLocation = -1;
int Game::s_ViewMatrixLocation = -1;

void Game::Init(){
    Logger::Init();
    Window::Init();
    UIDisplayManager::Init();

    Time::Init();
    SceneManager::Init();

    MatrixUtils::CreatePerspectiveProjection(s_ProjMatrix.GetData(), Mathf::ToRadians(80.0f), Window::GetAspectRatio(), 0.01f, 1000.0f);

    SceneManager::CreateScene<MainMenuScene>();

    player.Init();
    cave.Init();
    CORE_INFO("Initialized");
}
void Game::Shutdown(){
    CORE_INFO("Shutting Down");
    player.CleanUp();
    SceneManager::Shutdown();
    UIDisplayManager::Shutdown();
    Window::Shutdown();
    CORE_INFO("Shutdown");
}
void Game::Update(){
    Time::Update();
    //SceneManager::Update();
    //SceneManager::Draw();
    player.Update();
    cave.Draw();
    Input::Update();

    //Drawing
    Window::Update();
}

void Game::OnWindowResizeEvent(int width, int height){
    MatrixUtils::CreatePerspectiveProjection(s_ProjMatrix.GetData(), 90.0f, Window::GetAspectRatio(), 0.01f, 1000.0f);
    UIDisplayManager::OnWindowResizeEvent(width, height);
    SceneManager::OnWindowResizeEvent(width, height);
}

void Game::OnWindowFocusCallback(bool focused){
    
}
void Game::OnWindowPosCallback(int xPos, int yPos){

}

void Game::OnKeyEvent(int key, KeyAction action, unsigned char modifiers){
    SceneManager::OnKeyDownEvent(key, action, modifiers);
}

void Game::OnMouseButtonEvent(int button, bool isDown){
    SceneManager::OnMouseButtonEvent(button, isDown);
}