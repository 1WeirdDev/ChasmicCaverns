#pragma once

template <typename TYPE>
class Vec4{
public:
    Vec4() noexcept{}
    Vec4(TYPE vals){
        this->x = vals;
        this->y = vals;
        this->z = vals;
        this->w = vals;
    }
    Vec4(TYPE x, TYPE y, TYPE z, TYPE w) noexcept{
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    void SetXYZW(TYPE x, TYPE y, TYPE z, TYPE w) noexcept{
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    Vec4<TYPE> operator+(const Vec4<TYPE>& rhs) const noexcept{             
        Vec4<TYPE> vec;              
        vec.x = this->x + rhs.x;
        vec.y = this->y + rhs.y;
        vec.z = this->z + rhs.z;
        vec.w = this->w + rhs.w;
        return vec; // return the result by reference
    }
    Vec4<TYPE> operator-(const Vec4<TYPE>& rhs) const noexcept{             
        Vec4<TYPE> vec;              
        vec.x = this->x - rhs.x;
        vec.y = this->y - rhs.y;
        vec.z = this->z - rhs.z;
        vec.w = this->w - rhs.w;
        return vec; // return the result by reference
    }
    Vec4<TYPE> operator/(const Vec4<TYPE>& rhs) const noexcept
    {             
        Vec4<TYPE> vec;              
        vec.x = this->x / rhs.x;
        vec.y = this->y / rhs.y;
        vec.z = this->z / rhs.z;
        vec.w = this->w / rhs.w;
        return vec; // return the result by reference
    }
    Vec4<TYPE> operator*(const Vec4<TYPE>& rhs) const noexcept
    {             
        Vec4<TYPE> vec;              
        vec.x = this->x * rhs.x;
        vec.y = this->y * rhs.y;
        vec.z = this->z * rhs.z;
        vec.w = this->w * rhs.w;
        return vec; // return the result by reference
    }
    Vec4<TYPE> operator*(TYPE scalar) const noexcept
    {             
        Vec4<TYPE> vec(this->x * scalar, this->y * scalar, this->z * scalar, this->z * scalar);   
        return vec;
    }
    Vec4<TYPE>& operator/=(const Vec4<TYPE>& rhs)
    {                           
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        this->w /= rhs.w;
        return *this; // return the result by reference
    }
    Vec4<TYPE>& operator*=(const Vec4<TYPE>& rhs)
    {                           
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        this->w *= rhs.w;
        return *this; // return the result by reference
    }
    Vec4<TYPE>& operator+=(const Vec4<TYPE>& rhs)
    {                           
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
        return *this; // return the result by reference
    }

    Vec4<TYPE> GetNormalized() const noexcept{
        TYPE magnitude = GetMagnitude();
        if(magnitude == 0.0f)return Vec4<float>(0.0f);
        Vec4<TYPE> vec(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
        return vec;
    }
    TYPE GetDistance(Vec4<TYPE>& other) const noexcept{
        TYPE xs = other.x - x;
        TYPE ys = other.y - y;
        TYPE zs = other.z - z;
        TYPE ws = other.w - w;
        return (TYPE)(xs*2 + ys*2 + zs*2 + ws*2);
    }
    TYPE GetMagnitude() const noexcept{return (TYPE)sqrt(x * x + y * y + z * z + w * w);}
public:
    TYPE x = static_cast<TYPE>(0);
    TYPE y = static_cast<TYPE>(0);
    TYPE z = static_cast<TYPE>(0);
    TYPE w = static_cast<TYPE>(0);
};