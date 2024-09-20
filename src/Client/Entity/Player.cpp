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

    m_Position += moveDirection;

    Game::GetShader().Start();
    m_ViewMatrix.SetIdentity();

    //std::cout << data[0] << " " << data[1] << " " << data[2] << " " << data[3] << std::endl;
    // CORE_DEBUG("{0}, {1}, {2}, {3} | {4}, {5}, {6}, {7}", matrix[0].x, matrix[0].y, matrix[0].z, matrix[0].w, data[0], data[1], data[2], data[3])
    
    //testMatrix = glm::mat4x4(1.0f);
    //testMatrix = glm::rotate(testMatrix, m_Rotation.z, glm::vec3(1.0f, 0.0f, 0.0f));
    //testMatrix = glm::rotate(testMatrix, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    //testMatrix = glm::translate(testMatrix, glm::vec3(m_Position.x, 0, m_Position.z));
    //Create rotation matrix
    //Mat4x4 rotationMatrix;
    //MatrixUtils::CreateRotationMatrixAxisX(rotationMatrix.GetData(), m_Rotation.z);
    //MatrixUtils::MultiplyMat4x4(m_ViewMatrix.GetData(), m_ViewMatrix.GetData(), rotationMatrix.GetData());
    //MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), 1.0f, Vec3<float>(0.0f, 1.0f, 0.0f));

    //MatrixUtils::CreateRotationMatrixAxisY(rotationMatrix.GetData(), m_Rotation.y);
    //MatrixUtils::MultiplyMat4x4(m_ViewMatrix.GetData(), m_ViewMatrix.GetData(), rotationMatrix.GetData());
    
    //MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.z, Vec3<float>(1.0f, 0.0f, 0.0f));
    //MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.y, Vec3<float>(0.0f, 1.0f, 0.0f));
    //MatrixUtils::TranslateMat4x4<float>(m_ViewMatrix.GetData(), m_Position);
    
    //Shader::LoadMat4x4(Game::GetViewMatrixLocation(), m_ViewMatrix.GetData());
}
void Player::Draw(){

}