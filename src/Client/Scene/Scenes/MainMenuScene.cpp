#include "pch.h"
#include "MainMenuScene.h"
#include "GameScene.h"

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
            SceneManager::CreateScene<GameScene>();
            return true;
        }
        return false;
    });
    
    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);
}
void MainMenuScene::CleanUp() {
    m_Gui.CleanUp();
}
void MainMenuScene::Update() {
    
}
void MainMenuScene::Draw() {
    m_Gui.Draw();
}

bool MainMenuScene::OnMouseButtonEvent(int button, bool isDown, bool handled){
    if(handled)return false;
    return m_Gui.OnMouseButtonEvent(button, isDown);
}
void MainMenuScene::OnWindowResizeEvent(int width, int height){
    m_Gui.OnWindowResizeEvent(width, height);
}