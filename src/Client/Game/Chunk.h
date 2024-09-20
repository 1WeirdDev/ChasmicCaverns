#pragma once

#include "Rendering/BasicMesh.h"

class Chunk{
public:
    Chunk();
    ~Chunk();

    void Create();
    void CleanUp();

    void Draw() const;
private:
    BasicMesh m_Mesh;
};