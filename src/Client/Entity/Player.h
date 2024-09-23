#pragma once

#include "Math/Mat4x4.h"
#include "Math/Vec3.h"

class Player{
public:
    void Init();
    void CleanUp();

    void Update();
    void Draw();

    Vec3<float> GetPosition() const noexcept{return m_Position;}
    float* GetViewMatrix() const noexcept{return m_ViewMatrix.GetData();}
private:
    Vec3<float> m_Position;
    Vec3<float> m_Rotation;
    Mat4x4 m_ViewMatrix;
};