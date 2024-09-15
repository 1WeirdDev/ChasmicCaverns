#pragma once

#include "pch.h"
#include "Core/Logger.h"
#include "MeshData.h"

class TexturedMesh{
public:
    TexturedMesh(){}
    ~TexturedMesh(){}

    void CleanUp();

    void BindVao() const;
    
    void Create(unsigned char dimensions, VertexType vertexType, IndexType indexType, VertexType textureType, void* vertices, void* indices, void* textureCoords, size_t vertexCount, size_t indexCount, size_t textureCoordCount);
    void Draw() const;
    void DrawInstanced(size_t count) const;
    void DrawInstancedNoBinding(size_t count) const;
private:
    GLuint m_VaoId = 0;
    GLuint m_VboId = 0;
    GLuint m_EboId = 0;
    GLuint m_TboId = 0;
    GLuint m_GLIndexType = 0;
    size_t m_IndexCount = 0;
    bool m_IsCreated = false;
};