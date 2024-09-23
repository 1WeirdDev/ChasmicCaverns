#include "pch.h"
#include "Cave.h"

#include "Game.h"

Cave::Cave(){
}
Cave::~Cave(){}

void Cave::Init(){
    m_ChunkShader.Create();
    m_PointShader.Create();

    m_ChunkShader.Start();
    m_ChunkShader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());
    m_PointShader.Start();
    m_PointShader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());

    m_Region.SetCave(this);
    m_Region.CreateChunks();

    m_Texture.LoadFromPath("res/Textures/texture1.jpg");
}

void Cave::Draw() const{
    m_Texture.Load();
    m_Region.Draw();
}

void Cave::LoadViewMatrix(float* data) const noexcept{
    m_ChunkShader.Start();
    m_ChunkShader.LoadViewMatrix(data);
    m_PointShader.Start();
    m_PointShader.LoadViewMatrix(data);
}