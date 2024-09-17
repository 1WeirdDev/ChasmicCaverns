#include "pch.h"
#include "GameScene.h"

#include "Game.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Rendering/Gui/UIs/Frame.h"
#include "Rendering/Gui/UIs/Image.h"
#include "Rendering/Gui/UIs/Button.h"
#include "Rendering/Gui/UIDisplayManager.h"
#include "Scene/SceneManager.h"

GameScene::GameScene(){}
GameScene::~GameScene(){

}
void GameScene::Init() {
    float vertices[12]{
        0,0,-5,
        0,1,-5,
        1,0,-5,
        1,1,-5
    };

    unsigned int indices[6]{
        0,1,2,2,1,3
    };
    m_BasicMesh.Create(3, VT_FLOAT, FT_UNSIGNED_INT, &vertices, &indices, 12, 6);

    m_TextLabel = m_Gui.CreateChild<TextLabel>();
    m_TextLabel->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    m_TextLabel->SetText("Hello World");

    m_Player.Init();
    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);
}
void GameScene::CleanUp() {
    m_Player.CleanUp();
    m_Gui.CleanUp();
    m_BasicMesh.CleanUp();
}
void GameScene::Update() {
    m_Player.Update();
    m_TextLabel->SetText(std::to_string(Time::GetDeltaTime()).c_str());
}
void GameScene::Draw() {
    Game::GetShader().Start();
    m_Player.Draw();
    m_BasicMesh.Draw();
    m_Gui.Draw();
}

bool GameScene::OnMouseButtonEvent(int button, bool isDown){
    return m_Gui.OnMouseButtonEvent(button, isDown);
}
void GameScene::OnWindowResizeEvent(int width, int height){
    m_Gui.OnWindowResizeEvent(width, height);
}