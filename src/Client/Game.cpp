#include "pch.h"

#include "Game.h"
#include "Math/MatrixUtils.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes/MainMenuScene.h"
#include "Rendering/Gui/UIDisplayManager.h"
#include "Core/Mathf.h"

Cave Game::cave;
Mat4x4 Game::s_ProjMatrix;
Shader Game::s_Shader;
BasicMesh Game::s_BasicMesh;

int Game::s_ProjMatrixLocation = -1;
int Game::s_ViewMatrixLocation = -1;

void Game::Init(){
    Logger::Init();
    Window::Init();
    UIDisplayManager::Init();

    Time::Init();
    SceneManager::Init();

    s_Shader.CreateWithSource("#version 330 core\n in vec3 vertex; uniform mat4 proj_matrix; uniform mat4 view_matrix; \n void main(){gl_Position = proj_matrix * view_matrix * vec4(vertex, 1.0);}",
    "#version 330 core\n out vec4 color; void main() {color = vec4(1.0, 0.5, 0.5, 1.0);}");
    s_Shader.Start();

    s_ProjMatrix.SetIdentity();

    s_ProjMatrixLocation = s_Shader.GetUniformLocation("proj_matrix");
    s_ViewMatrixLocation = s_Shader.GetUniformLocation("view_matrix");
    MatrixUtils::CreatePerspectiveProjection(s_ProjMatrix.GetData(), Mathf::ToRadians(80.0f), Window::GetAspectRatio(), 0.01f, 1000.0f);
    s_Shader.LoadMat4x4(s_ProjMatrixLocation, s_ProjMatrix.GetData());

    SceneManager::CreateScene<MainMenuScene>();

    CORE_INFO("Initialized");
}
void Game::Shutdown(){
    CORE_INFO("Shutting Down");

    s_Shader.CleanUp();

    SceneManager::Shutdown();
    UIDisplayManager::Shutdown();
    Window::Shutdown();
    CORE_INFO("Shutdown");
}
void Game::Update(){
    Time::Update();
    //SceneManager::Update();
    //SceneManager::Draw();
    cave.Draw();
    Input::Update();

    //Drawing
    Window::Update();
}

void Game::OnWindowResizeEvent(int width, int height){
    s_Shader.Start();
    MatrixUtils::CreatePerspectiveProjection(s_ProjMatrix.GetData(), 90.0f, Window::GetAspectRatio(), 0.01f, 1000.0f);
    s_Shader.LoadMat4x4(s_ProjMatrixLocation, s_ProjMatrix.GetData());
    
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