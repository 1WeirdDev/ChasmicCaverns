#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(){}
Chunk::~Chunk(){
    CleanUp();
}

void Chunk::CreatePointData(){
    memset(m_PointData.data(), 0, sizeof(m_PointData));
    SetPointId(0,1,0, 1);
}
void Chunk::CreateMeshData(){
    uint8_t blockId = (uint8_t)((uint8_t)(IsPointEnabled(0,1,0) ? 1 : 0) | 
        (uint8_t)(IsPointEnabled(0,0,0) ? (uint8_t)FaceBit::FrontBottomLeft : 0) |
        (uint8_t)(IsPointEnabled(0,1,1) ? (uint8_t)FaceBit::BackTopLeft : 0) |
        (uint8_t)(IsPointEnabled(0,0,1) ? (uint8_t)FaceBit::BackBottomLeft : 0) |
        (uint8_t)(IsPointEnabled(1,1,0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
        (uint8_t)(IsPointEnabled(1,0,0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
        (uint8_t)(IsPointEnabled(1,1,1) ? (uint8_t)FaceBit::BackTopRight : 0) |
        (uint8_t)(IsPointEnabled(1,0,1) ? (uint8_t)FaceBit::BackBottomRight : 0));
    
    for(unsigned char x = 0; x < 6; x++){
        CreateData(blockId);

        //Shift the right to the left and get the new right sides data
        blockId <<= 4;
        blockId |=
        (IsPointEnabled(1,1,0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
        (IsPointEnabled(1,0,0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
        (IsPointEnabled(1,1,1) ? (uint8_t)FaceBit::BackTopRight : 0) |
        (IsPointEnabled(1,0,1) ? (uint8_t)FaceBit::BackBottomRight : 0);
    }
}
void Chunk::CreateMesh(){
    m_Mesh.Create(3, VT_UNSIGNED_CHAR, FT_UNSIGNED_SHORT, m_Vertices.data(), m_Indices.data(), m_Vertices.size(), m_Indices.size());
}

void Chunk::CleanUp(){
    m_Mesh.CleanUp();
}
void Chunk::Draw() const{
    m_Mesh.Draw();
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