#pragma once

#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Mesh/PointMesh.h"

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
public:
    Chunk();
    ~Chunk();

    void CreatePointData();
    void CreateMeshData();
    void CreateMesh();
    void CleanUp();

    void DrawPoints() const;
    void Draw() const;

    uint8_t GetPointId(uint8_t x, uint8_t y, uint8_t z) const noexcept;
    bool IsPointEnabled(uint8_t x, uint8_t y, uint8_t z) const noexcept;
    void SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept;
private:
    void CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
private:
    void AddVertex(uint8_t x, uint8_t y, uint8_t z) noexcept;
    void AddFaces(uint8_t amount);
    void CreateData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
private:
    std::array<uint8_t, ChunkWidth * ChunkWidth * ChunkHeight> m_PointData;
private:
    BasicMesh m_Mesh;
    std::vector<uint8_t> m_Vertices;
    std::vector<uint16_t> m_Indices;
    uint16_t m_VertexIndex = 0;
private:
#ifndef DIST
    PointMesh m_PointMesh;
    std::vector<uint8_t> m_PointVertices;
    std::vector<uint16_t> m_PointIndices;
    uint16_t m_PointVertexIndex = 0;
#endif
};