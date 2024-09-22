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
    m_BasicMesh.Create(3, VT_FLOAT, FT_UNSIGNED_INT, &vertices, &indices, 12, 6);

    m_TextLabel = m_Gui.CreateChild<TextLabel>();
    m_TextLabel->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    m_TextLabel->SetText("Hello World");

    Mat4x4 mat;
    float scale = 1.0f;
    MatrixUtils::CreateTranslationMatrix(mat.GetData(), 0, 0, -5.0f);
    MatrixUtils::ScaleMat4x4(mat.GetData(), scale, scale, -scale);

    m_Shader.Create();
    m_Shader.Start();
    m_Shader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());
    m_Shader.LoadScale(1.0f);

    m_Shader.LoadTransformationMatrix(mat.GetData());

    mat.SetIdentity();
    //the vertices will be 5 * larger on point mesh data
    scale = 1.0 / 8.0f;
    MatrixUtils::CreateTranslationMatrix(mat.GetData(), 0, 0, -5.0f);
    MatrixUtils::ScaleMat4x4(mat.GetData(), scale , scale, -scale);
    m_PointShader.Create();
    m_PointShader.Start();
    m_PointShader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());
    m_PointShader.LoadScale(1.0f);

    m_PointShader.LoadTransformationMatrix(mat.GetData());

    m_Chunk.CreatePointData();
    m_Chunk.CreateMeshData();
    m_Chunk.CreateMesh();

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
    m_TextLabel->SetText(std::to_string(1.0 / (double)Time::GetDeltaTime()).c_str());
}
void GameScene::Draw() {
    Game::GetShader().Start();
    m_Player.Draw();
    //m_BasicMesh.Draw();
    if(m_PolygonMode)glDisable(GL_CULL_FACE), m_PointShader.Start(), 
    m_Shader.LoadViewMatrix(m_Player.GetViewMatrix()), m_Chunk.DrawPoints();

    else glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode ? GL_LINE : GL_FILL);
    
    
    m_Shader.Start();
    m_Shader.LoadViewMatrix(m_Player.GetViewMatrix());

    m_Chunk.Draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
    m_Gui.Draw();
}
bool GameScene::OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers, bool handled){
    if(handled)return false;
    if(key == GLFW_KEY_R && action == KeyAction::Press){
        CORE_DEBUG("SWITCHING POLYGON MODE");
        m_PolygonMode = !m_PolygonMode;
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