#include "pch.h"
#include "MainMenuScene.h"

#include "Game.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Rendering/Gui/UIs/Frame.h"
#include "Rendering/Gui/UIs/Image.h"
#include "Rendering/Gui/UIs/Button.h"
#include "Rendering/Gui/UIDisplayManager.h"
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

    Frame* ui = m_Gui.CreateChild<Frame>();
    ui->SetSize(0.5f, 0.5f, 0, 0);
    ui->SetPosition(0.5f, 0.5f, 0, 0);
    //Dim2<float, int16_t>* size = &ui->GetSize();
    //size->m_ScaleX = 0.5f;
    //size->m_ScaleY = 0.5f;

    //UDim2<float, int16_t>* pos = &ui->GetPosition();
    //pos->m_ScaleX = 0.5;
    //pos->m_ScaleY = 0.25;

    //Frame* child = ui->CreateChild<Frame>();
    //size = &child->GetSize();
    //size->m_ScaleX = 0.5f;
    //size->m_ScaleY = 0.125f;
    //child->m_Color.y = 0;

    //pos = &child->GetPosition();
    //pos->m_OffsetX = 5;
    
    Image* image = ui->CreateChild<Image>();
    image->SetSize(0.5f, 0.5f,0,0);
    image->SetPosition(-0.5f,0,0,0);
    image->m_Visible = true;

    image = image->CreateChild<Image>();
    image->SetSize(0.5f, 0.5f,0,0);
    image->SetPosition(0,0,0,0);
    image->m_Visible = true;
    ui->CalculateGlobalData();

    Button* b = image->CreateChild<Button>();
    b->AddMouseButtonCallback([](int button, bool isDown){
        CORE_DEBUG("BUTTON CALLBACK");
        return false;
    });

    m_TextLabel = image->CreateChild<TextLabel>();
    Font* font = UIDisplayManager::GetFont("Arial");
    m_TextLabel->SetFont(font);
    m_TextLabel->SetText("FPS: 0");
    m_TextLabel->m_ZIndex = 0;

    CORE_DEBUG("CHILD COUNT {0}", image->GetChildCount());
    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);
}
void MainMenuScene::CleanUp() {
    m_Gui.CleanUp();
    m_BasicMesh.CleanUp();
    m_Player.CleanUp();
}
void MainMenuScene::Update() {
    m_Player.Update();
    m_TextLabel->SetText(std::to_string((int)floor(1.0f /  Time::GetDeltaTime())).c_str());
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