#pragma once

#include "Region.h"

#include "Rendering/Shaders/ChunkShader.h"
#include "Rendering/Shaders/PointShader.h"
#include "Rendering/Textures/Texture.h"

//Caves have regions
//Regions have chunks

class Cave{
public:
    Cave();
    ~Cave();
    
    void Init();

    void Draw() const;

    void LoadViewMatrix(float* data) const noexcept;

    void TogglePolygonMode(){m_PolygonMode = !m_PolygonMode;}

    const ChunkShader& GetChunkShader() const noexcept{return m_ChunkShader;}
    const PointShader& GetPointShader() const noexcept{return m_PointShader;}
    bool IsPolygonMode() const noexcept{return m_PolygonMode;}
private:
    ChunkShader m_ChunkShader;
    PointShader m_PointShader;
    Texture m_Texture;
    Region m_Region;
    bool m_PolygonMode = false;
};