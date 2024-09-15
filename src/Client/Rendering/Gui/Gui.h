#pragma once

#include "UI.h"

class Gui{
public:
    Gui();
    ~Gui();

    void CleanUp();
    void Draw() const;

    /// @brief Creates a new instance of a ui and adds it as a child
    /// @tparam UIType A type that derives from base class UI 
    /// @return returns the newly created instance of ui
    template <typename UIType>
    UIType* CreateChild(){
        UIType* ui = new UIType();
        m_Children.push_back(ui);
        return ui;
    }
    
    void OnWindowResizeEvent(int width, int height);
private:
    std::vector<UI*> m_Children;
};