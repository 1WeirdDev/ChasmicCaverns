#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(){}
Chunk::~Chunk(){
    CleanUp();
}

void Chunk::CreatePointData(){
    memset(m_PointData.data(), 0, sizeof(m_PointData));
    SetPointId(0,1,0, 1);
    SetPointId(2,1,0, 1);
    SetPointId(3,1,1, 1);
}
void Chunk::CreateMeshData(){
    uint8_t blockId = 0;
    for(uint8_t y = 0; y < ChunkHeight - 1; y++){
        for(uint8_t z = 0; z < ChunkWidth - 1; z++){
            blockId = (uint8_t)((uint8_t)(IsPointEnabled(0,y + 1,z) ? (uint8_t)FaceBit::FrontTopLeft : 0) | 
                (uint8_t)(IsPointEnabled(0, y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomLeft : 0) |
                (uint8_t)(IsPointEnabled(0, y + 1, z + 1) ? (uint8_t)FaceBit::BackTopLeft : 0) |
                (uint8_t)(IsPointEnabled(0, y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomLeft : 0) |
                (uint8_t)(IsPointEnabled(1, y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (uint8_t)(IsPointEnabled(1, y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (uint8_t)(IsPointEnabled(1, y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (uint8_t)(IsPointEnabled(1, y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0));
            for(uint8_t x = 0; x < ChunkWidth - 1; x++){
                //We do *2 because 1 is half of a block and 2 is a full point
                //Then we scale it in the shader
                CreateData(x* 2, y * 2, z * 2, blockId);

                //Create square
                //----
                float scale = 8.0f;
                uint8_t enabled = (uint8_t)IsPointEnabled(x, y, z) ? 1 : 0;
                m_PointVertices.push_back(x * 8 + 0);
                m_PointVertices.push_back(y * 8 + 0);
                m_PointVertices.push_back(z * 8 + 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * 8+ 0);
                m_PointVertices.push_back(y * 8+ 1);
                m_PointVertices.push_back(z * 8+ 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * 8 + 1);
                m_PointVertices.push_back(y * 8 + 0);
                m_PointVertices.push_back(z * 8 + 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * 8 + 1);
                m_PointVertices.push_back(y * 8 + 1);
                m_PointVertices.push_back(z * 8 + 0);
                m_PointVertices.push_back(enabled);

                m_PointVertices.push_back(x * 8 + 1);
                m_PointVertices.push_back(y * 8 + 0);
                m_PointVertices.push_back(z * 8 + 1);
                m_PointVertices.push_back(enabled);

                m_PointVertices.push_back(x * 8 + 1);
                m_PointVertices.push_back(y * 8 + 1);
                m_PointVertices.push_back(z * 8 + 1);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * 8 + 0);
                m_PointVertices.push_back(y * 8 + 0);
                m_PointVertices.push_back(z * 8 + 1);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * 8 + 0);
                m_PointVertices.push_back(y * 8 + 1);
                m_PointVertices.push_back(z * 8 + 1);
                m_PointVertices.push_back(enabled);
                
                m_PointIndices.push_back(m_PointVertexIndex + 0);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 3);

                m_PointIndices.push_back(m_PointVertexIndex + 4);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                m_PointIndices.push_back(m_PointVertexIndex + 7);
                m_PointVertexIndex+=8;
                //----

                //Shift the right to the left and get the new right sides data
                blockId <<= 4;
                blockId |=
                (IsPointEnabled(x + 1,y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (IsPointEnabled(x + 1,y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0);
            }
        }
    }
}
void Chunk::CreateMesh(){
    m_Mesh.Create(3, VT_UNSIGNED_CHAR, FT_UNSIGNED_SHORT, m_Vertices.data(), m_Indices.data(), m_Vertices.size(), m_Indices.size());
#ifndef DIST
    m_PointMesh.Create(m_PointVertices.data(), m_PointIndices.data(), m_PointVertices.size(), m_PointIndices.size());
#endif
}

void Chunk::CleanUp(){
#ifndef DIST
    m_PointMesh.CleanUp();
#endif
    m_Mesh.CleanUp();
}
void Chunk::Draw() const{
    m_Mesh.Draw();
}


void Chunk::DrawPoints() const{
#ifndef DIST
    m_PointMesh.Draw();
#endif
}

uint8_t Chunk::GetPointId(uint8_t x, uint8_t y, uint8_t z) const noexcept{
    if(x < 0 || y < 0 || z < 0 || x >= ChunkWidth || y >= ChunkHeight || z >= ChunkWidth)return 0;
    return m_PointData[(y * ChunkWidthSquared) + (z * ChunkWidth) + x];
}
bool Chunk::IsPointEnabled(uint8_t x, uint8_t y, uint8_t z) const noexcept{
    if(x < 0 || y < 0 || z < 0 || x >= ChunkWidth || y >= ChunkHeight || z >= ChunkWidth)return 0;
    return m_PointData[(y * ChunkWidthSquared) + (z * ChunkWidth) + x] > 0;
}
void Chunk::SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept{
    if(x < 0 || y < 0 || z < 0 || x >= ChunkWidth || y >= ChunkHeight || z >= ChunkWidth)return;
    m_PointData[(y * ChunkWidthSquared) + (z * ChunkWidth) + x] = id;
}