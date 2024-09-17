#pragma once

class Scene{
public:
    Scene();
    virtual ~Scene();

    virtual void Init();
    virtual void CleanUp();
    
    virtual void Update();
    virtual void Draw();

    virtual bool OnMouseButtonEvent(int button, bool isDown);
    virtual void OnWindowResizeEvent(int width, int height);
};