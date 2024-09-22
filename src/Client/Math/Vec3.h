#pragma once

template <typename TYPE>
class Vec3{
public:
    Vec3() noexcept{}
    Vec3(TYPE vals){
        this->x = vals;
        this->y = vals;
        this->z = vals;
    }
    Vec3(TYPE x, TYPE y, TYPE z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void SetXYZ(TYPE x, TYPE y, TYPE z) noexcept{
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3<TYPE> operator-() const noexcept{
        Vec3<TYPE> vec(-x, -y, -z);
        return vec;
    }
    Vec3<TYPE> operator+(const Vec3<TYPE>& rhs) const noexcept{             
        Vec3<TYPE> vec;              
        vec.x = this->x + rhs.x;
        vec.y = this->y + rhs.y;
        vec.z = this->z + rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator-(const Vec3<TYPE>& rhs) const noexcept{             
        Vec3<TYPE> vec;              
        vec.x = this->x - rhs.x;
        vec.y = this->y - rhs.y;
        vec.z = this->z - rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator/(const Vec3<TYPE>& rhs) const noexcept
    {             
        Vec3<TYPE> vec;              
        vec.x = this->x / rhs.x;
        vec.y = this->y / rhs.y;
        vec.z = this->z / rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator*(const Vec3<TYPE>& rhs) const noexcept
    {             
        Vec3<TYPE> vec;              
        vec.x = this->x * rhs.x;
        vec.y = this->y * rhs.y;
        vec.z = this->z * rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator*(TYPE scalar) const noexcept
    {             
        Vec3<TYPE> vec(this->x * scalar, this->y * scalar, this->z * scalar);   
        return vec; // return the result by reference
    }
    Vec3<TYPE>& operator/=(const Vec3<TYPE>& rhs)
    {                           
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        return *this; // return the result by reference
    }
    Vec3<TYPE>& operator*=(const Vec3<TYPE>& rhs)
    {                           
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this; // return the result by reference
    }
    Vec3<TYPE>& operator+=(const Vec3<TYPE>& rhs)
    {                           
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this; // return the result by reference
    }

    Vec3<TYPE> GetNormalized() const noexcept{
        TYPE magnitude = GetMagnitude();
        if(magnitude == 0.0f)return Vec3<float>(0.0f);
        Vec3<TYPE> vec(x / magnitude, y / magnitude, z / magnitude);
        return vec;
    }
    TYPE GetDistance(Vec3<TYPE>& other) const noexcept{
        TYPE xs = other.x - x;
        TYPE ys = other.y - y;
        TYPE zs = other.z - z;
        return (TYPE)(xs*2 + ys*2 + zs*2);
    }
    TYPE GetMagnitude() const noexcept{return (TYPE)sqrt(x * x + y * y + z * z);}
public:
    TYPE x = 0;
    TYPE y = 0;
    TYPE z = 0;
};