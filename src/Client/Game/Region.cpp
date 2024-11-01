#include "pch.h"

#include "Region.h"
#include "Cave.h"
#include "Game.h"

Region::Region(){}
Region::~Region(){}

void Region::SetCave(Cave* cave){
    m_Cave = cave;
}
void Region::CreateChunks(){
    for(uint8_t z = 0; z< RegionChunkWidth;z++){
        for(uint8_t x = 0; x< RegionChunkWidth;x++){
            unsigned int i = z * RegionChunkWidth + x;
            m_Chunks[i].SetPosition(x, 0, -z);
            m_Chunks[i].CreatePointData();
            m_Chunks[i].CreateMeshData();
            m_Chunks[i].CreateMesh();
        }
    }
}

void Region::Draw() const{
#ifndef DIST
    const PointShader& pointShader = m_Cave->GetPointShader();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    bool polygonMode = m_Cave->IsPolygonMode();
    if(polygonMode){
        //glDisable(GL_CULL_FACE);
        pointShader.Start();

        for(uint8_t i = 0; i < m_Chunks.size(); i++){
            pointShader.LoadTransformationMatrix(m_Chunks[i].GetPointTransformationMatrix());
            m_Chunks[i].DrawPoints();
        }
    }
    else{
        glEnable(GL_CULL_FACE);
    }
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);
    if(polygonMode){
        glLineWidth(2.0f);
        const ChunkDebugShader& chunkShader = m_Cave->GetDebugShader();
        chunkShader.Start();
        
        for(uint8_t i = 0; i < m_Chunks.size(); i++){
            chunkShader.LoadTransformationMatrix(m_Chunks[i].GetTransformationMatrix());
            m_Chunks[i].Draw();
        }
    }else{
        const ChunkShader& chunkShader = m_Cave->GetChunkShader();
        chunkShader.Start();
        
        for(uint8_t i = 0; i < m_Chunks.size(); i++){
            chunkShader.LoadTransformationMatrix(m_Chunks[i].GetTransformationMatrix());
            m_Chunks[i].Draw();
        }
    }
#else
    const ChunkShader& chunkShader = m_Cave->GetChunkShader();
    chunkShader.Start();
    
    for(uint8_t i = 0; i < m_Chunks.size(); i++){
        chunkShader.LoadTransformationMatrix(m_Chunks[i].GetTransformationMatrix());
        m_Chunks[i].Draw();
    }
#endif

#ifndef DIST
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
}