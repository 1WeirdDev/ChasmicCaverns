#pragma once

#include "../Scene.h"

#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Gui/UIs/TextLabel.h"
#include "Entity/Player.h"

#include "Rendering/Gui/Gui.h"

class MainMenuScene : public Scene{
public:
    MainMenuScene();
    ~MainMenuScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;
    
    bool OnMouseButtonEvent(int button, bool isDown, bool handled) override;
    void OnWindowResizeEvent(int width, int height) override;
private:
    Gui m_Gui;
};