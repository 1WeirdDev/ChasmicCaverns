#include "pch.h"

#include "BasicMesh.h"
#include "Core/Logger.h"

void BasicMesh::CleanUp(){
    if(!m_IsCreated)return;
    glDeleteBuffers(2, &m_VboId);
    glDeleteVertexArrays(1, &m_VaoId);
    m_VaoId = 0;
    m_VboId = 0;
    m_EboId = 0;
    m_IsCreated = false;
}
void BasicMesh::Create(unsigned char dimensions, VertexType vertexType, IndexType indexType, void* vertices, void* indices, size_t vertexCount, size_t indexCount){
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(2, &m_VboId);
    
    unsigned int glVertexType = (int)vertexType + 0x1400;    //GL HAS OFFSET 0x1400
    unsigned int dataSize = 0;
    switch(vertexType){
    case VertexType::Int8:
        dataSize = sizeof(int8_t);
        break;
    case VertexType::UInt8:
        dataSize = sizeof(uint8_t);
        break;
    case VertexType::Int16:
        dataSize = sizeof(int16_t);
        break;
    case VertexType::UInt16:
        dataSize = sizeof(uint16_t);
        break;
    case VertexType::Int32:
        dataSize = sizeof(int32_t);
        break;
    case VertexType::UInt32:
        dataSize = sizeof(uint32_t);
        break;
    case VertexType::Float:
        dataSize = sizeof(float);
        break;
    }

    glBindVertexArray(m_VaoId);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize * vertexCount, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dimensions, glVertexType, false, 0, nullptr);

    switch(indexType){ 
    case IndexType::UInt8:
        dataSize = sizeof(uint8_t);
        m_GLIndexType = GL_UNSIGNED_BYTE;
        break;
    case IndexType::UInt16:
        dataSize = sizeof(uint16_t);
        m_GLIndexType = GL_UNSIGNED_SHORT;
        break;
    case IndexType::UInt32:
        dataSize = sizeof(uint32_t);
        m_GLIndexType = GL_UNSIGNED_INT;
        break;
    default:
        CORE_WARN("Invalid Index Type for Basic mesh");
        break;
    }

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize * indexCount, indices, GL_STATIC_DRAW);
    m_VertexCount = vertexCount;
    m_IndexCount = indexCount;
    m_IsCreated = true;
}

void BasicMesh::Draw()const{
    if(!m_IsCreated)return;
    glBindVertexArray(m_VaoId);
    glDrawElements(GL_TRIANGLES, m_IndexCount, m_GLIndexType, nullptr);
}

void BasicMesh::DrawPoints() const{
    glDrawArrays(GL_POINTS, 0, m_VertexCount);
}