#include "pch.h"
#include "Chunk.h"

#include "Core/Logger.h"

//Half point is 1 Full is 2

#ifndef DIST
std::vector<uint8_t> casesFound;
#define PRNT_CASE(id, x, y, z) { \
    std::bitset<sizeof(uint8_t) * 8> bits(id); \
    CORE_DEBUG("CASE {0} AT ({1}, {2}, {3})", bits.to_string(), x + m_Position.x * ChunkWidth, y, ChunkWidth - z + m_Position.x * ChunkWidth);\
}
void PrintUnidentifiedCase(uint8_t bitsEnabled, uint8_t blockId)
{
    for(size_t i = 0; i < casesFound.size(); i++)if(casesFound[i] == blockId)return; \
    casesFound.push_back(blockId); \
    std::bitset<sizeof(uint8_t) * 8> bits(blockId);
    CORE_DEBUG("Unidentified case. Bits Enabled : {0} BlockId: 0b{1}", bitsEnabled, bits.to_string());
}
#else
#define PRNT_CASE(id, x, y, z)
void PrintUnidentifiedCase(uint8_t bitsEnabled, uint8_t blockId) {}
#endif

void Chunk::AddFaces(uint8_t amount)
{
    m_Indices.reserve(m_Indices.size() + amount * 3);
    for (uint8_t f = 0; f < amount; f++)
    {
        m_Indices.push_back(m_VertexIndex + 0);
        m_Indices.push_back(m_VertexIndex + 2);
        m_Indices.push_back(m_VertexIndex + 1);
        m_VertexIndex += 3;
    }
}

void Chunk::AddVertex(uint8_t x, uint8_t y, uint8_t z, uint8_t color) noexcept
{
    m_Vertices.reserve(m_Vertices.size() + 4);
    m_Vertices.push_back(x);
    m_Vertices.push_back(y);
    m_Vertices.push_back(z);
    m_Vertices.push_back(color);
}
void Chunk::CreateData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId)
{
    uint8_t bitsEnabled = 0;
    for (uint8_t x = 0; x < 8; x++)
    {
        if ((blockId >> x) & 1)
            bitsEnabled++;
    }

    switch (bitsEnabled)
    {
    case 0:
    case 8:
        break;
    case 1:
        CreateSingle(x, y, z, blockId);
        break;
    case 2:
        CreateDouble(x, y, z, blockId);
        break;
    case 3:
        switch(blockId){
        case 0b01100100:
            CreateSingle(x,y,z, 0b00100000);
            CreateDouble(x, y, z, 0b01000100);
            break;
        default:
            CreateTriple(x, y, z, blockId);
            break;
        }
        break;
    case 4:
        CreateQuadruple(x, y, z, blockId);
        break;
    case 7:
        switch(blockId){
        //Hide single edges
        case 0b01111111:
            AddVertex(x, y + 1, z    , GetPointIdFromVertexPos(x, y, z));
            AddVertex(x, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z + 2));
            AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x + 2, y + 2, z));
            AddFaces(1);
            break;
        case 0b10111111:
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z + 2));
            AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y + 2, z));
            AddVertex(x + 1, y, z, GetPointIdFromVertexPos(x + 2, y, z));
            AddFaces(1);
            break;
        case 0b11011111:
            AddVertex(x, y + 1, z + 2    , GetPointIdFromVertexPos(x, y, z + 2));
            AddVertex(x + 1, y + 2, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
            AddVertex(x, y + 2, z + 1    , GetPointIdFromVertexPos(x, y + 2, z));
            AddFaces(1);
            break;
        case 0b11101111:
            AddVertex(x + 1, y, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
            AddVertex(x, y + 1, z + 2, GetPointIdFromVertexPos(x, y + 2, z + 2));
            AddVertex(x, y, z + 1    , GetPointIdFromVertexPos(x, y, z));
            AddFaces(1);
            break;
        default:
            PrintUnidentifiedCase(bitsEnabled, blockId);
            break;
        }
        break;
    default:
        PrintUnidentifiedCase(bitsEnabled, blockId);
        break;
    }
}

void Chunk::CreateDouble(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId){
    switch(blockId){
    //Horizontal cases
    case 0b00001010:
        AddVertex(x + 2, y + 1, z + 0, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddVertex(x + 1, y + 2, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));

        AddVertex(x + 1, y + 2, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddVertex(x + 1, y + 2, z + 0, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddVertex(x + 2, y + 1, z + 0, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddFaces(2);
        break;
    case 0b11000000:
        AddVertex(x + 1, y + 0, z + 0, GetPointIdFromVertexPos(x, y, z));
        AddVertex(x + 0, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z));
        AddVertex(x + 0, y + 0, z + 1, GetPointIdFromVertexPos(x, y, z));

        AddVertex(x + 0, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z));
        AddVertex(x + 1, y + 0, z + 0, GetPointIdFromVertexPos(x, y, z));
        AddVertex(x + 1, y + 2, z + 0, GetPointIdFromVertexPos(x, y + 2, z));
        AddFaces(2);
        break;
    case 0b01000100:
        AddVertex(0,1,0, GetPointIdFromVertexPos(x, y, z));
        AddVertex(0,0,1, GetPointIdFromVertexPos(x, y, z));
        AddVertex(2,0,1, GetPointIdFromVertexPos(x + 2, y, z));

        AddVertex(2,0,1, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(2,1,0, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(0,1,0, GetPointIdFromVertexPos(x, y, z));
        AddFaces(2);
        break;
    //Opposite edges
    case 0b000010100:
        CreateSingle(x, y, z, 0b000010000);
        CreateSingle(x, y, z, 0b000000100);
        break;
    case 0b00100100:
        CreateSingle(x, y, z, 0b00100000);
        CreateSingle(x, y, z, 0b00000100);
        break;
    case 0b010000010:
        CreateSingle(x, y, z, 0b000000010);
        CreateSingle(x, y, z, 0b010000000);
        break;
    case 0b001000001:
        CreateSingle(x, y, z, 0b000000001);
        CreateSingle(x, y, z, 0b001000000);
        break;
    case 0b000101000:
        CreateSingle(x, y, z, 0b000001000);
        CreateSingle(x, y, z, 0b000100000);
        break;
    case 0b10000100:
        CreateSingle(x, y, z, 0b10000000);
        CreateSingle(x, y, z, 0b00000100);
        break;
    default:
        PrintUnidentifiedCase(2, blockId);
        break;
    }
}
void Chunk::CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId)
{
    switch (blockId)
    {
    case 0b10000000:
        AddVertex(x + 0, y + 1, z + 0, GetPointIdFromVertexPos(x, y + 2, z));
        AddVertex(x + 1, y + 2, z + 0, GetPointIdFromVertexPos(x, y + 2, z));
        AddVertex(x + 0, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z));
        AddFaces(1);
        break;
    case 0b01000000:
        AddVertex(x + 0, y + 0, z + 1, GetPointIdFromVertexPos(x, y, z));
        AddVertex(x + 1, y + 0, z + 0, GetPointIdFromVertexPos(x, y, z));
        AddVertex(x + 0, y + 1, z + 0, GetPointIdFromVertexPos(x, y, z));
        AddFaces(1);
        break;
    case 0b00100000:
        AddVertex(x + 0, y + 1, z + 2, GetPointIdFromVertexPos(x, y + 2, z + 2));
        AddVertex(x + 0, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z + 2));
        AddVertex(x + 1, y + 2, z + 2, GetPointIdFromVertexPos(x, y + 2, z + 2));
        AddFaces(1);
        break;
    case 0b00010000:
        AddVertex(x + 0, y + 0, z + 1, GetPointIdFromVertexPos(x, y, z + 2));
        AddVertex(x + 0, y + 1, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddVertex(x + 1, y + 0, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddFaces(1);
        break;
    case 0b00001000:
        AddVertex(x + 2, y + 1, z + 0, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddVertex(x + 1, y + 2, z + 0, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddFaces(1);
        break;
    case 0b00000100:
        AddVertex(x + 1, y + 0, z + 0, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(x + 2, y + 0, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(x + 2, y + 1, z + 0, GetPointIdFromVertexPos(x + 2, y, z));
        AddFaces(1);
        break;
    case 0b00000010:
        AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddVertex(x + 1, y + 2, z + 2, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddFaces(1);
        break;
    case 0b00000001:
        AddVertex(x + 1, y + 0, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
        AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
        AddVertex(x + 2, y + 0, z + 1, GetPointIdFromVertexPos(x + 2, y, z + 2));
        AddFaces(1);
        break;
    default:
        PrintUnidentifiedCase(1, blockId);
        break;
    }
}

void Chunk::CreateTriple(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId){
    switch(blockId){
        case 0b01000101:
            AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
            AddVertex(x + 2, y + 1, z, GetPointIdFromVertexPos(x + 2, y, z));

            AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x + 1, y, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));
            
            AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x + 2, y + 1, z + 2, GetPointIdFromVertexPos(x + 2, y, z + 2));

            AddFaces(3);
            break;
        case 0b01001100:
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
            AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));
            
            AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));
            AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z));
            
            AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));
            AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x + 2, y + 2, z));
            AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y, z));
            AddFaces(3);
            break;
        case 0b11000100:
            //AddVertex(x, y, z, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x, y, z + 1, GetPointIdFromVertexPos(x, y, z));
            AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
            AddVertex(x, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z));

            AddVertex(x, y + 2, z + 1, GetPointIdFromVertexPos(x, y + 2, z));
            AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z + 1));
            AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x, y + 2, z));
            
            AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
            AddVertex(x + 2, y + 1, z, GetPointIdFromVertexPos(x + 2, y, z));
            AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x, y + 2, z));

            AddFaces(3);
            break;
        case 0b11000010:
            //AddVertex(x, y, z, GetPointIdFromVertexPos(x, y, z));
            CreateDouble(x, y, z, 0b11000000);
            CreateSingle(x, y, z, 0b10);
            break;
        default:
            PrintUnidentifiedCase(3, blockId);
            break;
    }
}

void Chunk::CreateQuadruple(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId){
    switch(blockId){
    case 0b11000110:
        //AddVertex(x, y, z);
        CreateTriple(x, y, z, 0b11000100);
        CreateSingle(x, y, z, 0b10);
        break;
    case 0b01100101:
        CreateSingle(x, y, z, 0b00100000);
        CreateTriple(x, y, z, 0b01000101);
        break;
    case 0b01011100:
        AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x + 2, y + 2, z + 2));
        AddVertex(x, y + 1, z, GetPointIdFromVertexPos(x, y, z));
        AddVertex(x, y + 1, z + 2, GetPointIdFromVertexPos(x, y, z + 2));

        AddVertex(x, y + 1, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));
        AddVertex(x + 1, y + 2, z, GetPointIdFromVertexPos(x, y + 2, z + 2));

        AddVertex(x, y + 1, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(x + 2, y + 2, z + 1, GetPointIdFromVertexPos(x + 2, y + 2, z));

        AddVertex(x + 1, y, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddVertex(x + 2, y, z + 1, GetPointIdFromVertexPos(x + 2, y, z));
        AddVertex(x, y + 1, z + 2, GetPointIdFromVertexPos(x, y, z + 2));
        AddFaces(4);
        break;
    default:
        PrintUnidentifiedCase(4, blockId);
        break;
    }
}