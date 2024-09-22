#include "pch.h"

#include "Player.h"
#include "Core/Time.h"
#include "Core/Mathf.h"
#include "Math/MatrixUtils.h"
#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>

void Player::Init(){

}
void Player::CleanUp(){
}
void Player::Update(){
    m_Rotation.y += 35 * Input::GetMouseDeltaX() * Time::GetDeltaTime();
    m_Rotation.z -= 35 * Input::GetMouseDeltaY() * Time::GetDeltaTime();

    m_Rotation.z = Mathf::Clamp(m_Rotation.z, Mathf::ToRadians(-90.0f), Mathf::ToRadians(90.0f));

    Vec3<float> moveDirection(0.0f);
    if(Input::IskeyDown(GLFW_KEY_S)){
        moveDirection.x += (float)sin(m_Rotation.y) * Time::GetDeltaTime();
        moveDirection.z -= (float)cos(m_Rotation.y) * Time::GetDeltaTime();
    }if(Input::IskeyDown(GLFW_KEY_W)){
        moveDirection.x -= (float)sin(m_Rotation.y) * Time::GetDeltaTime();
        moveDirection.z += (float)cos(m_Rotation.y) * Time::GetDeltaTime();
    }
    
    if(Input::IskeyDown(GLFW_KEY_A)){
        moveDirection.x -= (float)sin(m_Rotation.y - Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
        moveDirection.z += (float)cos(m_Rotation.y - Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
    }if(Input::IskeyDown(GLFW_KEY_D)){
        moveDirection.x -= (float)sin(m_Rotation.y + Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
        moveDirection.z += (float)cos(m_Rotation.y + Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
    }

    float speed = 10;
    m_Position += moveDirection * speed;

    Game::GetShader().Start();
    m_ViewMatrix.SetIdentity();
    
    glm::mat4x4 test;
    glm::scale(test, glm::vec3(1, 1, 1));
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.z, Vec3<float>(1.0f, 0.0f, 0.0f));
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.y, Vec3<float>(0.0f, 1.0f, 0.0f));
    MatrixUtils::TranslateMat4x4<float>(m_ViewMatrix.GetData(), m_Position);
    
    Shader::LoadMat4x4(Game::GetViewMatrixLocation(), m_ViewMatrix.GetData());
}
void Player::Draw(){

}