#pragma once

#include "pch.h"
#include "Scene.h"

class SceneManager{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    static void Draw();

    static void OnWindowResizeEvent(int width, int height);

    template<typename SCENE>
    static SCENE* CreateScene(){
        SCENE* scene = new SCENE();
        s_Scenes.push_back(scene);
        scene->Init();
        return scene;
    }

    static bool RemoveScene(Scene* scene);
private:
    static std::vector<Scene*> s_Scenes;
};