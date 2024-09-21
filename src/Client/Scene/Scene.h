#pragma once

#include "Input/Input.h"

class Scene{
public:
    Scene();
    virtual ~Scene();

    virtual void Init();
    virtual void CleanUp();
    
    virtual void Update();
    virtual void Draw();

    virtual bool OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers, bool handled){return false;}
    virtual bool OnMouseButtonEvent(int button, bool isDown, bool handled){return false;}
    virtual void OnWindowResizeEvent(int width, int height);
};