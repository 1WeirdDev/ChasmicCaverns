#pragma once

#include "Chunk.h"
#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Shaders/ChunkShader.h"

class Cave;
class Region{
public:
    static constexpr uint8_t RegionChunkWidth = 1;
    Region();
    ~Region();

    void SetCave(Cave* cave);

    void CreateChunks();

    void Draw() const;
private:
    Cave* m_Cave = nullptr;
    ChunkShader shader;
    BasicMesh mesh;
    std::array<Chunk, RegionChunkWidth * RegionChunkWidth> m_Chunks;
};