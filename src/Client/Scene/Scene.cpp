#include "pch.h"

#include "Scene.h"

Scene::Scene(){}
Scene::~Scene(){}
void Scene::Init(){}
void Scene::CleanUp(){}
void Scene::Update(){}
void Scene::Draw(){}

bool Scene::OnMouseButtonEvent(int button, bool isDown){return false;}
void Scene::OnWindowResizeEvent(int width, int height){
    
}