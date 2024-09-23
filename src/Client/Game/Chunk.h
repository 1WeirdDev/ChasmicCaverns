#pragma once

#include "Rendering/Mesh/TexturedMesh.h"
#include "Rendering/Mesh/PointMesh.h"
#include "Math/Mat4x4.h"
#include "Math/Vec3.h"

enum class FaceBit{
    FrontTopLeft =      (uint8_t)(1 << 7),
    FrontBottomLeft =   (uint8_t)(1 << 6),
    BackTopLeft =       (uint8_t)(1 << 5),
    BackBottomLeft =    (uint8_t)(1 << 4),
    FrontTopRight =     (uint8_t)(1 << 3),
    FrontBottomRight =  (uint8_t)(1 << 2),
    BackTopRight =      (uint8_t)(1 << 1),
    BackBottomRight =   (uint8_t)(1 << 0)
};

class Chunk{
public:
    static constexpr uint8_t ChunkWidth = 20;
    static constexpr uint8_t ChunkHeight = 20;
    static constexpr uint16_t ChunkWidthSquared = ChunkWidth * ChunkWidth;
    static constexpr uint8_t PointScale = 8;
public:
    Chunk();
    ~Chunk();

    void SetPosition(int8_t x, int8_t y, int8_t z);

    void CreatePointData();
    void CreateMeshData();
    void CreateMesh();
    void CleanUp();

    void DrawPoints() const;
    void Draw() const;

    uint8_t GetPointId(uint8_t x, uint8_t y, uint8_t z) const noexcept;
    bool IsPointEnabled(uint8_t x, uint8_t y, uint8_t z) const noexcept;
    void SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept;

    float* GetTransformationMatrix() const noexcept{return m_TransformationMatrix.GetData();}
private:
    void CreateDouble(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
    void CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
private:
    void AddVertex(uint8_t x, uint8_t y, uint8_t z) noexcept;
    void AddFaces(uint8_t amount);
    void CreateData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
private:
    std::array<uint8_t, ChunkWidth * ChunkWidth * ChunkHeight> m_PointData;
private:
    //Position in chunks not global position
    Vec3<int8_t> m_Position;
    Mat4x4 m_TransformationMatrix;
    TexturedMesh m_Mesh;
    std::vector<uint8_t> m_Vertices;
    std::vector<uint16_t> m_Indices;
    std::vector<uint8_t> m_TextureCoords;
    uint16_t m_VertexIndex = 0;
    //Debug
#ifndef DIST
private:
    Mat4x4 m_PointTransformationMatrix;
    PointMesh m_PointMesh;
    std::vector<uint8_t> m_PointVertices;
    std::vector<uint16_t> m_PointIndices;
    uint16_t m_PointVertexIndex = 0;
public:
    float* GetPointTransformationMatrix() const noexcept{return m_PointTransformationMatrix.GetData();}
#endif
};