#pragma once

template <typename TYPE>
class Vec2{
public:
    Vec2() noexcept{}
    Vec2(TYPE vals){
        this->x = vals;
        this->y = vals;
    }
    Vec2(TYPE x, TYPE y){
        this->x = x;
        this->y = y;
    } 
    Vec2<TYPE> operator+(const Vec2<TYPE>& rhs)const{             
        Vec2<TYPE> vec;              
        vec.x = this->x + rhs.x;
        vec.y = this->y + rhs.y;
        return vec; // return the result by reference
    }
    Vec2<TYPE> operator-(const Vec2<TYPE>& rhs)const{             
        Vec2<TYPE> vec;              
        vec.x = this->x - rhs.x;
        vec.y = this->y - rhs.y;
        return vec; // return the result by reference
    }
    Vec2<TYPE> operator/(const Vec2<TYPE>& rhs) const
    {             
        Vec2<TYPE> vec;              
        vec.x = this->x / rhs.x;
        vec.y = this->y / rhs.y;
        return vec; // return the result by reference
    }

    Vec2<TYPE> operator*(const Vec2<TYPE>& rhs)
    {             
        Vec2<TYPE> vec;              
        vec.x = this->x * rhs.x;
        vec.y = this->y * rhs.y;
        return vec; // return the result by reference
    }
     Vec2<TYPE>& operator/=(const Vec2<TYPE>& rhs)
    {                           
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this; // return the result by reference
    }
    Vec2<TYPE>& operator*=(const Vec2<TYPE>& rhs)
    {                           
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this; // return the result by reference
    }
    Vec2<TYPE>& operator+=(const Vec2<TYPE>& rhs)
    {                           
        this->x += rhs.x;
        this->y += rhs.y;
        return *this; // return the result by reference
    }

    void SetData(TYPE x, TYPE y){
        this->x = x;
        this->y = y;
    }

    TYPE GetMagnitude() const noexcept{return (TYPE)sqrt(x * x + y * y);}
public:
    TYPE x = 0;
    TYPE y = 0;
};