#pragma once

template <typename TYPE>
class Vec3{
public:
    Vec3() noexcept{}
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
    Vec3<TYPE> operator+(const Vec3<TYPE>& rhs){             
        Vec3<TYPE> vec;              
        vec.x = this->x + rhs.x;
        vec.y = this->y + rhs.y;
        vec.z = this->z + rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator-(const Vec3<TYPE>& rhs){             
        Vec3<TYPE> vec;              
        vec.x = this->x - rhs.x;
        vec.y = this->y - rhs.y;
        vec.z = this->z - rhs.z;
        return vec; // return the result by reference
    }
    Vec3<TYPE> operator/(const Vec3<TYPE>& rhs)
    {             
        Vec3<TYPE> vec;              
        vec.x = this->x / rhs.x;
        vec.y = this->y / rhs.y;
        vec.z = this->z / rhs.z;
        return vec; // return the result by reference
    }

    Vec3<TYPE> operator*(const Vec3<TYPE>& rhs)
    {             
        Vec3<TYPE> vec;              
        vec.x = this->x * rhs.x;
        vec.y = this->y * rhs.y;
        vec.z = this->z * rhs.z;
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

    template <typename ReturnType>
    ReturnType GetDistance(Vec3<TYPE>& other){
        ReturnType xs = other.x - x;
        ReturnType ys = other.y - y;
        ReturnType zs = other.z - z;
        return (ReturnType)(xs*2 + ys*2 + zs*2);
    }
    TYPE GetMagnitude() const noexcept{return (TYPE)sqrt(x * x + y * y + z * z);}
public:
    TYPE x = 0;
    TYPE y = 0;
    TYPE z = 0;
};