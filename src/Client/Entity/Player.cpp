#include "pch.h"

#include "Player.h"
#include "Core/Time.h"
#include "Math/MatrixUtils.h"
#include "Game.h"

void Player::Init(){

}
void Player::CleanUp(){

}
void Player::Update(){
    m_Position.x += Time::GetDeltaTime() * 0.5f;
    
    Game::GetShader().Start();
    m_ViewMatrix.SetIdentity();
    MatrixUtils::TranslateMat4x4<float>(m_ViewMatrix.GetData(), m_Position);
    Shader::LoadMat4x4(Game::GetViewMatrixLocation(), m_ViewMatrix.GetData());
}
void Player::Draw(){

}