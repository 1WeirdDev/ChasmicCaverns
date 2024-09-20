#pragma once

#include "Core/Time.h"
#include "Core/Logger.h"
#include "Rendering/Window.h"
#include "Rendering/Shader.h"
#include "Rendering/BasicMesh.h"
#include "Math/Mat4x4.h"
#include "Input/Input.h"

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
    static const Shader& GetShader() noexcept {return s_Shader;}
    static int GetViewMatrixLocation() noexcept{return s_ViewMatrixLocation;}
private:
    static Mat4x4 s_ProjMatrix;
    static Shader s_Shader;
    static BasicMesh s_BasicMesh;
    
    static int s_ProjMatrixLocation;
    static int s_ViewMatrixLocation;
};