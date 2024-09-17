#pragma once

#include "../Scene.h"

#include "Rendering/BasicMesh.h"
#include "Rendering/Gui/UIs/TextLabel.h"
#include "Entity/Player.h"

#include "Rendering/Gui/Gui.h"

class GameScene : public Scene{
public:
    GameScene();
    ~GameScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;
    
    bool OnMouseButtonEvent(int button, bool isDown) override;
    void OnWindowResizeEvent(int width, int height) override;
private:
    Player m_Player;
    BasicMesh m_BasicMesh;
    Gui m_Gui;
    TextLabel* m_TextLabel = nullptr;
};