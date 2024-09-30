#include "pch.h"
#include "ChunkShader.h"

#include "Core/Logger.h"

void ChunkShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    in vec3 vertex;\n \
    in vec2 textureCoord;\n \
    out vec2 textureCoords;\n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformationMatrix;\n \
    uniform vec2 position;\n \
    void main(){ \
    textureCoords = textureCoord;\n \
    gl_Position = vec4(vertex, 1.0);}";

    const char* fragmentShaderData = "#version 330 core\n \
    in vec2 textureCoords;\n \
    out vec4 color; \
    uniform sampler2D textureMap;\n \
    void main(){ \
    color = vec4(0.0, 0.0, 0.0, 1.0);\n \
    //color = texture(textureMap, textureCoords);\n \
    }";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformationMatrix");
    m_PositionLocation = GetUniformLocation("position");
    CORE_DEBUG("Compiled Chunk Shader");
}

void ChunkShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void ChunkShader::LoadViewMatrix(float* data) const noexcept{
    LoadMat4x4(m_ViewMatrixLocation, data);
}
void ChunkShader::LoadTransformationMatrix(float* data) const noexcept{
    LoadMat4x4(m_TransformationMatrixLocation, data);
}
void ChunkShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}