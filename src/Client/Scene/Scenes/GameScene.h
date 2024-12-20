#pragma once

#include "../Scene.h"

#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Gui/UIs/TextLabel.h"
#include "Entity/Player.h"

#include "Rendering/Gui/Gui.h"
#include "Rendering/Shaders/ChunkShader.h"
#include "Rendering/Shaders/PointShader.h"
#include "Game/Cave.h"

class GameScene : public Scene{
public:
    GameScene();
    ~GameScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;

    bool OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers, bool handled) override;
    bool OnMouseButtonEvent(int button, bool isDown, bool handled) override;
    void OnWindowResizeEvent(int width, int height) override;
private:
    /*
    PointShader m_PointShader;
    ChunkShader m_Shader;
    Chunk m_Chunk;*/
    Cave m_Cave;
    Player m_Player;
    BasicMesh m_BasicMesh;
    Gui m_Gui;
    TextLabel* m_PositionLabel = nullptr;
    TextLabel* m_FPSLabel = nullptr;
};