#pragma once

#include "Region.h"

#include "Rendering/Shaders/ChunkShader.h"
#include "Rendering/Shaders/PointShader.h"
#include "Rendering/Shaders/ChunkDebugShader.h"
#include "Rendering/Textures/Texture.h"
#include "Math/Frustum.h"

//Caves have regions
//Regions have chunks

class Cave{
public:
    Cave();
    ~Cave();
    
    void Init();

    void Draw() const;

    void LoadViewMatrix(float* data) noexcept;

    void TogglePolygonMode(){m_PolygonMode = !m_PolygonMode;}

    const ChunkShader& GetChunkShader() const noexcept{return m_ChunkShader;}
    const PointShader& GetPointShader() const noexcept{return m_PointShader;}
    const ChunkDebugShader& GetDebugShader() const noexcept{return m_DebugShader;}
    bool IsPolygonMode() const noexcept{return m_PolygonMode;}
private:
    ChunkShader m_ChunkShader;
#ifndef DIST
    PointShader m_PointShader;
    ChunkDebugShader m_DebugShader;
#endif
    Frustum m_Frustum;
    Texture m_Texture;
    Region m_Region;
    bool m_PolygonMode = false;
};