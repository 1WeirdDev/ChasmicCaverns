#include "pch.h"
#include "UI.h"

#include "Rendering/Window.h"
#include "Core/Logger.h"
UI::UI() : m_Position(0,0,0,0), m_GlobalPosition(0,0), m_GlobalSize(1,1){}
UI::~UI(){}


void UI::DeleteChildren(){
    for(size_t i = 0; i < m_Children.size(); i++){
        delete m_Children[i];
    }

    m_Children.resize(0);
}
void UI::SetPosition(float scaleX, float scaleY, uint16_t offsetX, uint16_t offsetY){
    m_Position.m_ScaleX = scaleX;
    m_Position.m_ScaleY = scaleY;
    m_Position.m_OffsetX = offsetX;
    m_Position.m_OffsetY = offsetY;
}

void UI::SetSize(float scaleX, float scaleY, uint16_t offsetX, uint16_t offsetY){
    m_Size.m_ScaleX = scaleX;
    m_Size.m_ScaleY = scaleY;
    m_Size.m_OffsetX = offsetX;
    m_Size.m_OffsetY = offsetY;
}
void UI::CalculateGlobalData() noexcept{
    m_GlobalPosition.SetData(m_Position.m_ScaleX, m_Position.m_ScaleY);
    m_GlobalSize.SetData(1,1);

    if(m_Parent){
        Vec2<float> parentPosition = m_Parent->GetGlobalPosition();
        Vec2<float>& parentSize = m_Parent->GetGlobalSize();
        m_GlobalPosition *= parentSize;
        m_GlobalPosition += m_Parent->GetGlobalPosition();

        m_GlobalSize *= parentSize;
    }

    m_GlobalPosition.x += m_Position.m_OffsetX * Window::GetPixelSizeX();
    m_GlobalPosition.y += m_Position.m_OffsetY * Window::GetPixelSizeY();

    m_GlobalSize.x *= m_Size.m_ScaleX;
    m_GlobalSize.y *= m_Size.m_ScaleY;

    m_GlobalSize.x += m_Size.m_OffsetX * Window::GetPixelSizeX();
    m_GlobalSize.y += m_Size.m_OffsetY * Window::GetPixelSizeY();

    for(size_t i = 0; i < m_Children.size(); i++){
        m_Children[i]->CalculateGlobalData();
    }
}
void UI::CallChildrenWindowResizeEvent(int width, int height){
    for(size_t i = 0; i < m_Children.size(); i++){
        m_Children[i]->OnWindowResizeEvent(width, height);
        m_Children[i]->CallChildrenWindowResizeEvent(width, height);
    }
}