#include "pch.h"
#include "Chunk.h"

#include "Math/MatrixUtils.h"

Chunk::Chunk(){}
Chunk::~Chunk(){
    CleanUp();
}

void Chunk::CreatePointData(){
    memset(m_PointData.data(), 0, sizeof(m_PointData));
    SetPointId(0,1,1, 1);
    SetPointId(2,1,0, 1);
    SetPointId(3,1,1, 1);
    
    SetPointId(2,1,2, 1);
    /*;
    
    srand(time(NULL));
    for(unsigned char y = 0; y < ChunkWidth; y++){
        for(unsigned char z = 0; z < ChunkWidth; z++){
            for(unsigned char x = 0; x < ChunkWidth; x++){
                
                int value = rand() % 15;
                SetPointId(x , y, z, value > 0 ? 1 : 0);
            }
        }
    }
    */

    for(unsigned char x = 0; x < 5; x++){
        for(unsigned char y = 0; y < 5; y++){
            CreateSingle(x, y, 0, 1);
        }
   }
}
void Chunk::CreateMeshData(){
    uint8_t blockId = 0;
    m_Vertices.resize(0);
    m_Indices.resize(0);
    m_VertexIndex = 0;
    for(uint8_t y = 0; y < ChunkHeight - 1; y++){
        for(uint8_t z = 0; z < ChunkWidth - 1; z++){
            blockId = (uint8_t)((uint8_t)(IsPointEnabled(0, y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0));


            for(uint8_t x = 0; x < ChunkWidth - 1; x++){
                //We do *2 because 1 is half of a block and 2 is a full point
                //Then we scale it in the shader
                blockId <<= 4;
                blockId &= 0b11110000;
                blockId |=
                (IsPointEnabled(x + 1,y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (IsPointEnabled(x + 1,y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0);

                CreateData(x* 2, y * 2, z * 2, blockId);
            }
        }
    }
    
#ifndef DIST
    for(uint8_t y = 0; y < ChunkHeight; y++){
        for(uint8_t z = 0; z < ChunkWidth; z++){
            for(uint8_t x = 0; x < ChunkWidth; x++){
                //Create square
                //----
                //This scale has nothing to do with chunk vertices but only points
                //The point scale will be 1/scale at scale * vertexPos
                uint8_t enabled = (uint8_t)IsPointEnabled(x, y, z) ? 1 : 0;
                m_PointVertices.push_back(x * PointScale + 0);
                m_PointVertices.push_back(y * PointScale + 0);
                m_PointVertices.push_back(z * PointScale + 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * PointScale + 0);
                m_PointVertices.push_back(y * PointScale + 1);
                m_PointVertices.push_back(z * PointScale + 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * PointScale + 1);
                m_PointVertices.push_back(y * PointScale + 0);
                m_PointVertices.push_back(z * PointScale + 0);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * PointScale + 1);
                m_PointVertices.push_back(y * PointScale + 1);
                m_PointVertices.push_back(z * PointScale + 0);
                m_PointVertices.push_back(enabled);

                m_PointVertices.push_back(x * PointScale + 1);
                m_PointVertices.push_back(y * PointScale + 0);
                m_PointVertices.push_back(z * PointScale + 1);
                m_PointVertices.push_back(enabled);

                m_PointVertices.push_back(x * PointScale + 1);
                m_PointVertices.push_back(y * PointScale + 1);
                m_PointVertices.push_back(z * PointScale + 1);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * PointScale + 0);
                m_PointVertices.push_back(y * PointScale + 0);
                m_PointVertices.push_back(z * PointScale + 1);
                m_PointVertices.push_back(enabled);
                
                m_PointVertices.push_back(x * PointScale + 0);
                m_PointVertices.push_back(y * PointScale + 1);
                m_PointVertices.push_back(z * PointScale + 1);
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
                
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 0);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 7);
                
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 3);
                m_PointIndices.push_back(m_PointVertexIndex + 4);
                m_PointIndices.push_back(m_PointVertexIndex + 4);
                m_PointIndices.push_back(m_PointVertexIndex + 3);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 0);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 4);
                
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 7);
                m_PointIndices.push_back(m_PointVertexIndex + 3);
                m_PointIndices.push_back(m_PointVertexIndex + 3);
                m_PointIndices.push_back(m_PointVertexIndex + 7);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                m_PointVertexIndex+=8;
                //----
            }
        }
    }
#endif
}
void Chunk::CreateMesh(){
    CORE_DEBUG("Creating chunk mesh with {0} Vertices, {1} Indices", m_Vertices.size(), m_Indices.size());
    m_Mesh.Create(3, VT_UNSIGNED_CHAR, FT_UNSIGNED_SHORT, VT_UNSIGNED_CHAR, m_Vertices.data(), m_Indices.data(), m_TextureCoords.data(), m_Vertices.size(), m_Indices.size(), m_TextureCoords.size());
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
    if(x < 0 || y < 0 || z < 0 || x >= ChunkWidth || y >= ChunkHeight || z >= ChunkWidth)return false;
    return m_PointData[(y * ChunkWidthSquared) + (z * ChunkWidth) + x] > 0;
}
void Chunk::SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept{
    if(x < 0 || y < 0 || z < 0 || x >= ChunkWidth || y >= ChunkHeight || z >= ChunkWidth)return;
    m_PointData[(y * ChunkWidthSquared) + (z * ChunkWidth) + x] = id;
}


void Chunk::SetPosition(int8_t x, int8_t y, int8_t z){
    m_Position.SetXYZ(x, y, z);

    //We invert the z axis for the transformation matrix and add The chunkWidth to compensate
    z+= 1;
    MatrixUtils::TranslateMat4x4(m_TransformationMatrix.GetData(), Vec3<float>(x * ChunkWidth, y * ChunkHeight, z * ChunkWidth));
    float scale = 0.5f;
    MatrixUtils::ScaleMat4x4(m_TransformationMatrix.GetData(), scale , scale, -scale);

#ifndef DIST
    MatrixUtils::TranslateMat4x4(m_PointTransformationMatrix.GetData(), Vec3<float>(x * ChunkWidth, y * ChunkHeight, z * ChunkWidth));
    scale = (1.0f / PointScale);
    MatrixUtils::ScaleMat4x4(m_PointTransformationMatrix.GetData(), scale , scale, -scale);
#endif
}