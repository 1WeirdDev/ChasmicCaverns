#pragma once

#include "Math/Mat4x4.h"
#include "Math/Vec3.h"

#include <glm/mat4x4.hpp>

class Player{
public:
    void Init();
    void CleanUp();

    void Update();
    void Draw();

    //float* GetViewMatrix() const noexcept{return (float*)&testMatrix[0][0];}
    float* GetViewMatrix() const noexcept{return m_ViewMatrix.GetData();}
private:
    Vec3<float> m_Position;
    Vec3<float> m_Rotation;
    Mat4x4 m_ViewMatrix;
    glm::mat4x4 testMatrix;
};