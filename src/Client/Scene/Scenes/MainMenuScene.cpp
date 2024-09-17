#include "pch.h"
#include "MainMenuScene.h"

#include "Game.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Rendering/Gui/UIs/Frame.h"
#include "Rendering/Gui/UIs/Image.h"
#include "Rendering/Gui/UIs/Button.h"
#include "Rendering/Gui/UIDisplayManager.h"
#include "Scene/SceneManager.h"

MainMenuScene::MainMenuScene(){}
MainMenuScene::~MainMenuScene(){

}
void MainMenuScene::Init() {
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

    m_Player.Init();

    UI* parent = m_Gui.CreateChild<UI>();
    parent->SetSize(0.25f, 0.25f, 0, 0);
    parent->SetPosition(0.5f, 0.5f, 0, 0);
    parent->m_Visible = false;

    Frame* frame = parent->CreateChild<Frame>();
    frame->SetSize(0.5f, 0.5f, 0, 0);
    frame->SetPosition(-0.25f, -0.25f, 0, 0);

    TextLabel* textLabel = frame->CreateChild<TextLabel>();
    textLabel->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    textLabel->SetText("Play");
    textLabel->CalculateGlobalData();

    Button* b = frame->CreateChild<Button>();
    b->AddMouseButtonCallback([this](int button, bool isDown){
        if(button == 0){
            SceneManager::DeleteScene(this);
            return true;
        }
        return false;
    });
    
    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);
}
void MainMenuScene::CleanUp() {
    m_Gui.CleanUp();
    m_BasicMesh.CleanUp();
    m_Player.CleanUp();
}
void MainMenuScene::Update() {
    m_Player.Update();
    //m_TextLabel->SetText(std::to_string((int)floor(1.0f /  Time::GetDeltaTime())).c_str());
}
void MainMenuScene::Draw() {
    Game::GetShader().Start();
    //m_BasicMesh.Draw();
    m_Player.Draw();
    m_Gui.Draw();
}

bool MainMenuScene::OnMouseButtonEvent(int button, bool isDown){
    return m_Gui.OnMouseButtonEvent(button, isDown);
}
void MainMenuScene::OnWindowResizeEvent(int width, int height){
    m_Gui.OnWindowResizeEvent(width, height);
}