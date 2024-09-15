#pragma once

template<typename ScaleType, typename OffsetType>
class UDim2{
public:
    UDim2(){
        m_ScaleX = 1;
        m_ScaleY = 1;
        m_OffsetX = 0;
        m_OffsetY = 0;
    }
    UDim2(ScaleType scaleX, ScaleType scaleY, OffsetType offsetX, OffsetType offsetY){
        m_ScaleX = scaleX;
        m_ScaleY = scaleY;
        m_OffsetX = offsetX;
        m_OffsetY = offsetY;
    }

    ScaleType m_ScaleX;
    ScaleType m_ScaleY;
    OffsetType m_OffsetX;
    OffsetType m_OffsetY;
};