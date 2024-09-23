#pragma once

#include "Chunk.h"

class Cave;
class Region{
public:
    static constexpr uint8_t RegionChunkWidth = 10;
    Region();
    ~Region();

    void SetCave(Cave* cave);

    void CreateChunks();

    void Draw() const;
private:
    Cave* m_Cave = nullptr;
    std::array<Chunk, RegionChunkWidth * RegionChunkWidth> m_Chunks;
};