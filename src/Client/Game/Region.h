#pragma once

#include "Chunk.h"
#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Shader.h"

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
    Shader shader;
    BasicMesh mesh;
    std::array<Chunk, RegionChunkWidth * RegionChunkWidth> m_Chunks;
};