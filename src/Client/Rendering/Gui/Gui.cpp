#include "pch.h"
#include "Gui.h"

#include "UIDisplayManager.h"

Gui::Gui(){}
Gui::~Gui(){}

void Gui::CleanUp(){
    for(size_t i = 0; i < m_Children.size(); i++){
        delete m_Children[i];
    }
    m_Children.resize(0);
}

void Gui::Draw() const{
    for(size_t i = 0; i < m_Children.size(); i++){
        UIDisplayManager::DrawUI(m_Children[i], 0);
    }
}

void Gui::OnWindowResizeEvent(int width, int height){
    for(size_t i = 0; i < m_Children.size(); i++){
        m_Children[i]->CalculateGlobalData();

        //TODO MAYBE: instead of a whole window resize event manually check if its a textlable or textbox and update it
        m_Children[i]->OnWindowResizeEvent(width, height);
        m_Children[i]->CallChildrenWindowResizeEvent(width, height);
    }
}