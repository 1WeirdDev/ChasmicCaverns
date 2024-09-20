#include <pch.h>

#include "MatrixUtils.h"
#include "Core/Logger.h"
#include "Core/Mathf.h"
#include "Mat4x4.h"
#include "Vec4.h"

void MatrixUtils::MultiplyMat4x4(float* dst, float* first, float* second){
    float data[16];
    memset(data, 0, sizeof(data));

    for (unsigned char row = 0; row < 4; ++row) {
        for (unsigned char col = 0; col < 4; ++col) {
            for (unsigned char k = 0; k < 4; ++k) {
                data[col * 4 + row] += GetMat4Data(first, row, k) * GetMat4Data(second, k, col);
            }
        }
    }

    for(unsigned char i = 0; i < 16; i++)
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

void MatrixUtils::CreatePerspectiveProjection(float* dst, float fovInRadians, float aspectRatio, float pNear, float pFar) {
    float tanHalfFovy = std::tan(fovInRadians / 2.0f);
    SetMat4Data(dst, 0, 0, 1.0f / (aspectRatio * tanHalfFovy));
    SetMat4Data(dst, 1, 1, (1.0f / tanHalfFovy));
    SetMat4Data(dst, 2, 2, - (pFar + pNear) / (pFar - pNear));
    SetMat4Data(dst, 3, 2, - 1.0f);
    SetMat4Data(dst, 2, 3, -(2.0f * pFar * pNear) / (pFar - pNear));
    SetMat4Data(dst, 3, 3, 0.0f);
}
#pragma endregion
#pragma region Translation

//Translation

void MatrixUtils::TranslateMat4x4(float* dst, float x, float y, float z)noexcept{
    Vec4<float> row1 = Vec4(dst[0], dst[1], dst[2], dst[3]);
    Vec4<float> row2 = Vec4(dst[4], dst[5], dst[6], dst[7]);
    Vec4<float> row3 = Vec4(dst[8], dst[9], dst[10], dst[11]);
    Vec4<float> row4 = Vec4(dst[12], dst[13], dst[14], dst[15]);
    Vec4<float> data = row1 * x + row2 * y + row3 * z + row4;
    dst[12] = data.x;
    dst[13] = data.y;
    dst[14] = data.z;
    dst[15] = data.w;
}
#pragma endregion

#pragma region Rotation
void MatrixUtils::RotateMat4x4(float* dst, float angle, Vec3<float> _axis) noexcept{
    float const a = angle;
	float const c = cos(a);
	float const s = sin(a);

	Vec3<float> axis(_axis.GetNormalized());
	Vec3<float> temp(axis* (1.0f - c));

    float rotate[16];
	SetMat4Data(rotate, 0, 0, c + temp.x * axis.x);
	SetMat4Data(rotate, 1, 0, temp.x * axis.y + s * axis.z);
	SetMat4Data(rotate, 2, 0,(temp.x * axis.z - s * axis.y));

	SetMat4Data(rotate, 0, 1, temp.y * axis.x - s * axis.z);
	SetMat4Data(rotate, 1, 1, c + temp.y * axis.y);
	SetMat4Data(rotate, 2, 1, temp.y * axis.z + s * axis.x);

	SetMat4Data(rotate, 0, 2, temp.z * axis.x + s * axis.y);
	SetMat4Data(rotate, 1, 2, temp.z * axis.y - s * axis.x);
	SetMat4Data(rotate, 2, 2, c + temp.z * axis.z);

    Vec4<float> row1 = Vec4(dst[0], dst[1], dst[2], dst[3]);
    Vec4<float> row2 = Vec4(dst[4], dst[5], dst[6], dst[7]);
    Vec4<float> row3 = Vec4(dst[8], dst[9], dst[10], dst[11]);

    Vec4<float> f1 = row1 * GetMat4Data(rotate, 0, 0) + row2 * GetMat4Data(rotate,1,0) + row3 * GetMat4Data(rotate, 2,0);
    Vec4<float> f2 = row1 * GetMat4Data(rotate, 0, 1) + row2 * GetMat4Data(rotate,1,1) + row3 * GetMat4Data(rotate, 2,1);
    Vec4<float> f3 = row1 * GetMat4Data(rotate, 0, 2) + row2 * GetMat4Data(rotate,1,2) + row3 * GetMat4Data(rotate, 2,2);

    dst[0] = f1.x;
    dst[1] = f1.y;
    dst[2] = f1.z;

    dst[4] = f2.x;
    dst[5] = f2.y;
    dst[6] = f2.z;

    dst[8] = f3.x;
    dst[9] = f3.y;
    dst[10] = f3.z;
}
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