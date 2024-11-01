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

    //Loading Colors
    m_ChunkShader.LoadColor(0, 0.5, 0.5, 0.0);
    m_ChunkShader.LoadColor(1, 0.5, 0.5, 0.0);
    m_ChunkShader.LoadColor(2, 2.0f / 255.0f, 48.0f / 255.0f, 32.0f / 255.0f);
    m_PointShader.Start();
    m_PointShader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());

    m_DebugShader.Create();
    m_DebugShader.LoadProjectionMatrix(Game::GetProjectionMatrix().GetData());

    m_Region.SetCave(this);
    m_Region.CreateChunks();

    m_Texture.LoadFromPath("res/Textures/texture1.jpg");
    CORE_DEBUG("Initialized Cave");
}

void Cave::Draw() const{
    m_Texture.Load();
    m_Region.Draw();
}

void Cave::LoadViewMatrix(float* data) noexcept{
    m_ChunkShader.Start();
    m_ChunkShader.LoadViewMatrix(data);
    m_PointShader.Start();
    m_PointShader.LoadViewMatrix(data);
    m_DebugShader.Start();
    m_DebugShader.LoadViewMatrix(data);

    Mat4x4 view(data);
    Mat4x4 progViewMatrix = Game::GetProjectionMatrix() * view;
    m_Frustum.ExtractFrustumPlanes(progViewMatrix);
}