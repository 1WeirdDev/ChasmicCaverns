#include <pch.h>

#include "MatrixUtils.h"

void MatrixUtils::MultiplyMat4x4(float* dst, float* first, float* second){
    float data[16];
    memset(data, 0, sizeof(data));

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int k = 0; k < 4; ++k) {
                data[col * 4 + row] += GetMat4Data(first, row, k) * GetMat4Data(second, k, col);
            }
        }
    }

    for(unsigned int i = 0; i < 16; i++)
        dst[i] = data[i];
}

#pragma region Projection
void MatrixUtils::CreateOrthoProjection(float* dst, float pNear, float pFar, float left, float right, float top, float bottom){
    // Set the matrix values according to the orthographic projection formul
    SetMat4Data(dst, 0, 0, 2.0f / (right - left));
    SetMat4Data(dst, 0,3, -(right + left / right - left));

    SetMat4Data(dst, 1, 1, 2.0f / (top - bottom));
    SetMat4Data(dst, 1,3, -(top + bottom / top - bottom));
    //SetMat4Data(dst, 2,2,- 2.0f / (pFar - pNear));
    //SetMat4Data(dst, 3,2,- (pFar + pNear) / (pFar - pNear));
}

void MatrixUtils::CreatePerspectiveProjection(float* dst, float fovInDegrees, float aspectRatio, float pNear, float pFar) {
    float tanHalfFov = std::tan((fovInDegrees * 0.0174533f)/ 2.0f);
    SetMat4Data(dst, 0, 0, 1.0f / (aspectRatio * tanHalfFov));
    SetMat4Data(dst, 1, 1, 1.0f / tanHalfFov);
    SetMat4Data(dst, 2, 2, -(pFar + pNear) / (pFar - pNear));
    SetMat4Data(dst, 2, 3, -(2 * pFar * pNear) / (pFar - pNear));
    SetMat4Data(dst, 3, 2, -1.0f);
}
#pragma endregion
#pragma region Translation

//Translation

void MatrixUtils::TranslateMat4x4(float* dst, float x, float y, float z)noexcept{
    AddMat4DataBy(dst, 0, 3, x);
    AddMat4DataBy(dst, 1, 3, y);
    AddMat4DataBy(dst, 2, 3, z);
}
#pragma endregion

#pragma region Rotation
void MatrixUtils::CreateRotationMatrixAxisX(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 1,1, cos(angleInRadians));
    SetMat4Data(dst, 1,2, -sin(angleInRadians));
    SetMat4Data(dst, 2,1, sin(angleInRadians));
    SetMat4Data(dst, 2,2, cos(angleInRadians));
}
void MatrixUtils::CreateRotationMatrixAxisY(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 0,0, cos(angleInRadians));
    SetMat4Data(dst, 0,2, sin(angleInRadians));
    SetMat4Data(dst, 2,0, -sin(angleInRadians));
    SetMat4Data(dst, 2,2, cos(angleInRadians));
}
void MatrixUtils::CreateRotationMatrixAxisZ(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 0,0, cos(angleInRadians));
    SetMat4Data(dst, 0,1, -sin(angleInRadians));
    SetMat4Data(dst, 1,0, sin(angleInRadians));
    SetMat4Data(dst, 1,1, cos(angleInRadians));
}
#pragma endregion