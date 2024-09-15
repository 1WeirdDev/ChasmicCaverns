#pragma once
#include <string.h>

class Mat4x4{
public:
    Mat4x4(){
        SetIdentity();
    }
    ~Mat4x4(){}

    void SetIdentity() noexcept{
        memset(&data, 0, sizeof(data));
        SetValue(0,0, 1.0f);
        SetValue(1,1, 1.0f);
        SetValue(2,2, 1.0f);
        SetValue(3,3, 1.0f);
    }

    inline float GetValue(unsigned char row, unsigned char col) const noexcept{
        return data[col * 4 + row];
    }
    inline void SetValue(unsigned char row, unsigned char col, float value) noexcept{
        if(row < 0 || row > 3 || col < 0 || col > 3)return;
        
        data[col * 4 + row] = value;
    }

    float* GetData() const{return (float*)data;}
private:
    float data[16];
};