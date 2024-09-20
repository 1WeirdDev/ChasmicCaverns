#pragma once
#include <string.h>

#include "Vec4.h"
class Mat4x4{
public:
    Mat4x4(){
        SetIdentity();
    }
    ~Mat4x4(){}

    void SetIdentity() noexcept{
        memset(&m_Data, 0, sizeof(m_Data));
        SetValue(0,0, 1.0f);
        SetValue(1,1, 1.0f);
        SetValue(2,2, 1.0f);
        SetValue(3,3, 1.0f);
    }

    inline float GetValue(unsigned char row, unsigned char col) const noexcept{
        return m_Data[col * 4 + row];
    }
    inline void SetValue(unsigned char row, unsigned char col, float value) noexcept{
        if(row < 0 || row > 3 || col < 0 || col > 3)return;

        m_Data[col * 4 + row] = value;
    }
    Vec4<float> operator [](int row) const {
        std::cout << "W" << GetValue(0, row) << std::endl;
        return Vec4(GetValue(0, row),GetValue(1, row),GetValue(2, row),GetValue(3, row));
    }

    float* GetData() const noexcept{return (float*)m_Data;}
private:
    float m_Data[16];
};