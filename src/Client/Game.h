#pragma once

#include "Core/Time.h"
#include "Core/Logger.h"
#include "Rendering/Window.h"
#include "Rendering/Shader.h"
#include "Rendering/Mesh/BasicMesh.h"
#include "Math/Mat4x4.h"
#include "Input/Input.h"
#include "Entity/Player.h"

#include "Game/Cave.h"

class Game{
public:
    static void Init();
    static void Shutdown();

    static void Update();

    static void OnWindowResizeEvent(int width, int height);
    static void OnWindowPosCallback(int xPos, int yPos);

    static void OnWindowFocusCallback(bool focused);
    static void OnMouseButtonEvent(int button, bool isDown);
    static void OnKeyEvent(int key, KeyAction action, unsigned char modifiers);

    static Mat4x4& GetProjectionMatrix() noexcept{return s_ProjMatrix;}
    static int GetViewMatrixLocation() noexcept{return s_ViewMatrixLocation;}

    static Player& GetPlayer() noexcept{return player;}
private:
    static Cave cave;
    static Player player;
    static Mat4x4 s_ProjMatrix;
    static BasicMesh s_BasicMesh;
    
    static int s_ProjMatrixLocation;
    static int s_ViewMatrixLocation;
};