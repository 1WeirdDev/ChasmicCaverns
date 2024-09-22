#include "pch.h"
#include "Chunk.h"

#include "Core/Logger.h"

#ifndef DIST
void PrintUnidentifiedCase(uint8_t bitsEnabled, uint8_t blockId)
{
    std::bitset<sizeof(uint8_t) * 8> bits(blockId);
    CORE_DEBUG("Unidentified case. Bits Enabled : {0} BlockId: 0b0{1}", bitsEnabled, bits.to_string());
}
#else
void PrintUnidentifiedCase(uint8_t bitsEnabled, uint8_t blockId) {}
#endif

void Chunk::AddFaces(uint8_t amount)
{
    for (uint8_t f = 0; f < amount; f++)
    {
        m_Indices.push_back(m_VertexIndex + 0);
        m_Indices.push_back(m_VertexIndex + 1);
        m_Indices.push_back(m_VertexIndex + 2);
    }
    m_VertexIndex += 3;
}

void Chunk::AddVertex(uint8_t x, uint8_t y, uint8_t z) noexcept
{
    m_Vertices.reserve(m_Vertices.size() + 3);
    m_Vertices.push_back(x);
    m_Vertices.push_back(y);
    m_Vertices.push_back(z);
}
void Chunk::CreateData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId)
{
    uint8_t bitsEnabled = 0;
    for (uint8_t x = 0; x < 8; x++)
    {
        if ((blockId >> x) & 1)
            bitsEnabled++;
    }

    CORE_DEBUG("Creating data for {0} bits enabled {1}", blockId, bitsEnabled);

    switch (bitsEnabled)
    {
    case 0:
    case 8:
        break;
    case 1:
        CreateSingle(x, y, z, blockId);
        break;
    default:
        PrintUnidentifiedCase(bitsEnabled, blockId);
        break;
    }
}

void Chunk::CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId)
{
    switch (blockId)
    {
    case 0b00000001:
        AddVertex(x + 0, y + 1, z + 0);
        AddVertex(x + 1, y + 0, z + 0);
        AddVertex(x + 0, y + 0, z + 1);
        AddFaces(1);
        break;
    default:
        PrintUnidentifiedCase(1, blockId);
        break;
    }
}