#pragma once

#include "pch.h"
#include "Scene.h"

class SceneManager{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    static void Draw();

    static void OnKeyDownEvent(int key, KeyAction action, unsigned char modifiers);
    static void OnMouseButtonEvent(int button, bool isDown);
    static void OnWindowResizeEvent(int width, int height);

    template<typename SCENE>
    static SCENE* CreateScene(){
        SCENE* scene = new SCENE();
        s_Scenes.push_back(scene);
        scene->Init();
        return scene;
    }

    /// @brief Removes the scene if its found without deleting it
    /// @param scene the Scene* we are seaching
    /// @return true if we were able to remove it false if not
    static bool RemoveScene(Scene* scene);

    /// @brief Searches for specified scene in scenes list and deletes it
    /// @param scene The Scene* we are searching for
    /// @return true if we were able to delete it false if not
    static bool DeleteScene(Scene* scene);
private:
    static std::vector<Scene*> s_Scenes;
};