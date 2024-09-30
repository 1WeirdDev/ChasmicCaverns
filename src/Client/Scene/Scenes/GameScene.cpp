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
#include "Math/MatrixUtils.h"

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
    m_BasicMesh.Create(3, VT_FLOAT, FT_UINT32, &vertices, &indices, 12, 6);
    
    Frame* f = m_Gui.CreateChild<Frame>();
    f->SetSize(0.25f, 0.25f, 0, 0);
    f->SetPosition(0, 0, 0, 0);
    m_PositionLabel = f->CreateChild<TextLabel>();
    m_PositionLabel->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    m_PositionLabel->SetText("0, 0, 0");
    m_PositionLabel->SetPosition(0,0.0f, 0, 0);

    m_FPSLabel = m_Gui.CreateChild<TextLabel>();
    m_FPSLabel->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    m_FPSLabel->SetText("0FPS");
    m_FPSLabel->SetPosition(0,1, 0, -100);
    m_FPSLabel->SetSize(0.2f, 0.1f, 0, 0);

    //m_PointShader.LoadTransformationMatrix(mat.GetData());

    //m_Cave.Init();
    //m_Chunk.CreatePointData();
    //m_Chunk.CreateMeshData();
    //m_Chunk.CreateMesh();
//
    //m_Chunk.SetPosition(0, 0, 0);
    //m_Player.Init();
    m_Cave.Init();
    Window::SetBackgroundColor(0.5f, 0.5f, 0.5f);
}
void GameScene::CleanUp() {
    m_Player.CleanUp();
    m_Gui.CleanUp();
    m_BasicMesh.CleanUp();
}
void GameScene::Update() {
    m_Player.Update();
    m_FPSLabel->SetText(("FPS: " + std::to_string((int)(1.0 / (double)Time::GetDeltaTime()))).c_str());

    Vec3<float> position = m_Player.GetPosition();
    m_PositionLabel->SetText((std::to_string((int)position.x) + ", " + std::to_string((int)position.y) + ", " + std::to_string((int)position.z)).c_str());
    m_Cave.LoadViewMatrix(m_Player.GetViewMatrix());
}
void GameScene::Draw() {
    m_Player.Draw();
    m_Cave.Draw();
    //
    glClear(GL_DEPTH_BUFFER_BIT);
    m_Gui.Draw();
}
bool GameScene::OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers, bool handled){
    if(handled)return false;
    if(key == GLFW_KEY_R && action == KeyAction::Press){
        m_Cave.TogglePolygonMode();
    }
    return false;
}
bool GameScene::OnMouseButtonEvent(int button, bool isDown, bool handled){
    if(handled)return false;
    return m_Gui.OnMouseButtonEvent(button, isDown);
}
void GameScene::OnWindowResizeEvent(int width, int height){
    m_Gui.OnWindowResizeEvent(width, height);
}