#pragma once

#include "../UI.h"
#include "Math/Vec3.h"

class Frame : public UI{
public:
    Frame() : m_Color(1.0f, 1.0f, 1.0f) {m_UIType = UT_Frame;}
    ~Frame(){DeleteChildren();}

    Vec3<float> m_Color;
private:

};