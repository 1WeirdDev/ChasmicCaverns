#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(){}
Chunk::~Chunk(){
    CleanUp();
}

void Chunk::Create(){
    uint8_t vertices[12]{
        0,0,0,
        0,1,0,
        1,0,0,
        1,1,0
    };
    
    uint32_t indices[6]{
        0,1,2,2,1,3
    };
    m_Mesh.Create(3, VT_UNSIGNED_CHAR, FT_UNSIGNED_INT, &vertices, &indices, 12, 6);
}

void Chunk::CleanUp(){
    
}
void Chunk::Draw() const{
    m_Mesh.Draw();
}