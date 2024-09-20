#pragma once

#include "Vec3.h"

class MatrixUtils{
public:
    static float ToRadians(float degrees){return degrees * 0.0174533f;}

    static inline float GetMat4Data(float* dst, unsigned char r, unsigned char c) {return dst[c * 4 + r];}
    static inline void SetMat4Data(float* dst, unsigned char r, unsigned char c, float f){ dst[c * 4 + r] = f;}
    static inline void MultiplyMat4DataBy(float* dst, unsigned char r, unsigned char c, float f){dst[c * 4 + r] *= f;}
    static inline void AddMat4DataBy(float* dst, unsigned char r, unsigned char c, float f){ dst[c * 4 + r] += f;}

    //Any functions here marked noexcept will never crash unless you pass invalid data

    static void MultiplyMat4x4(float* dst, float* first, float* second);

    //Projection
    static void CreateOrthoProjection(float* dst, float pNear, float pFar, float left, float right, float top, float bottom);
    static void CreatePerspectiveProjection(float* dst, float fovInRadians, float aspectRatio, float pNear, float pFar);

    //Translation
    static void TranslateMat4x4(float* dst, float x, float y, float z) noexcept;

    //Rotation
    static void RotateMat4x4(float* dst, float angle, Vec3<float> axis) noexcept;
    static void CreateRotationMatrixAxisX(float* dst, float angleInRadians)noexcept;
    static void CreateRotationMatrixAxisY(float* dst, float angleInRadians)noexcept;
    static void CreateRotationMatrixAxisZ(float* dst, float angleInRadians)noexcept;

#pragma region Templates

    /// @brief 
    /// @tparam TYPE Specifies that the TYPE of vector3 is. So Vec3<TYPE> 
    /// @param dst the src and dst of the matrix we are translating
    /// @param vector the vector we are translating by
    template <typename TYPE>
    static void TranslateMat4x4(float* dst, const Vec3<TYPE>& vector) noexcept{
        /*
        */
        Vec4<float> row0 = Vec4(dst[0], dst[1], dst[2], dst[3]);
        Vec4<float> row1 = Vec4(dst[4], dst[5], dst[6], dst[7]);
        Vec4<float> row2 = Vec4(dst[8], dst[9], dst[10], dst[11]);
        Vec4<float> row3 = Vec4(dst[12], dst[13], dst[14], dst[15]);
        Vec4<float> data = row0 * vector.x + row1 * vector.y + row2 * vector.z + row3;
        dst[12] = data.x;
        dst[13] = data.y;
        dst[14] = data.z;
        dst[15] = data.w;
    }
#pragma endregion
private:
};