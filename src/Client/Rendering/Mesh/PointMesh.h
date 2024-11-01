#pragma once

#include "pch.h"
#include "MeshData.h"

class PointMesh{
public:
    PointMesh(){}
    ~PointMesh(){}

    void CleanUp();

    void BindVao() const;
    
    void Create(uint8_t* vertices, uint16_t* indices, size_t vertexCount, size_t indexCount);
    void Draw() const;
    void DrawPoints() const;
    void DrawInstanced(size_t count) const;
    void DrawInstancedNoBinding(size_t count) const;
public:
    size_t GetVertexCount() const noexcept {return m_VertexCount;}
    size_t GetIndexCount() const noexcept{return m_IndexCount;}
private:
    GLuint m_VaoId = 0;
    GLuint m_VboId = 0;
    GLuint m_EboId = 0;
    GLuint m_TboId = 0;
    GLuint m_GLIndexType = 0;
    size_t m_VertexCount = 0;
    size_t m_IndexCount = 0;
    bool m_IsCreated = false;
};