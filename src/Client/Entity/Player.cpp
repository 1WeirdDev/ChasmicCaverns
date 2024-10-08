#include "pch.h"

#include "Player.h"
#include "Core/Time.h"
#include "Core/Mathf.h"
#include "Math/MatrixUtils.h"
#include "Game.h"

void Player::Init(){

}
void Player::CleanUp(){
}
void Player::Update(){
    m_Rotation.y += 0.01f * Input::GetMouseDeltaX();
    m_Rotation.z -= 0.01f * Input::GetMouseDeltaY();

    m_Rotation.z = Mathf::Clamp(m_Rotation.z, Mathf::ToRadians(-90.0f), Mathf::ToRadians(90.0f));

    Vec3<float> moveDirection(0.0f);
    if(Input::IsKeyDown(GLFW_KEY_S)){
        moveDirection.x -= (float)sin(m_Rotation.y) * Time::GetDeltaTime();
        moveDirection.z += (float)cos(m_Rotation.y) * Time::GetDeltaTime();
    }if(Input::IsKeyDown(GLFW_KEY_W)){
        moveDirection.x += (float)sin(m_Rotation.y) * Time::GetDeltaTime();
        moveDirection.z -= (float)cos(m_Rotation.y) * Time::GetDeltaTime();
    }

    if(Input::IsKeyDown(GLFW_KEY_A)){
        moveDirection.x += (float)sin(m_Rotation.y - Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
        moveDirection.z -= (float)cos(m_Rotation.y - Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
    }if(Input::IsKeyDown(GLFW_KEY_D)){
        moveDirection.x += (float)sin(m_Rotation.y + Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
        moveDirection.z -= (float)cos(m_Rotation.y + Mathf::ToRadians(90.0f)) * Time::GetDeltaTime();
    }

    if(Input::IsKeyDown(GLFW_KEY_SPACE)){
        moveDirection.y += Time::GetDeltaTime();
    }
    if(Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT)){
        moveDirection.y -= Time::GetDeltaTime();
    }

    float speed = 10;
    m_Position += moveDirection * speed;
    
    m_ViewMatrix.SetIdentity();

    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.z, Vec3<float>(1.0f, 0.0f, 0.0f));
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.y, Vec3<float>(0.0f, 1.0f, 0.0f));
    MatrixUtils::TranslateMat4x4<float>(m_ViewMatrix.GetData(), -m_Position);
}
void Player::Draw(){
    //CORE_DEBUG("PLR POSITION ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
}