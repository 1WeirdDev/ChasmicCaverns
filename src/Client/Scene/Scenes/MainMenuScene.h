#pragma once

#include "../Scene.h"

#include "Rendering/BasicMesh.h"
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

    void OnWindowResizeEvent(int width, int height) override;
private:
    Player m_Player;
    BasicMesh m_BasicMesh;
    Gui m_Gui;
    TextLabel* m_TextLabel = nullptr;
};