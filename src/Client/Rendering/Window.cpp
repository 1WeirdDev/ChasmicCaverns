#include "pch.h"

#include "Core.h"
#include "Window.h"
#include "Core/Logger.h"
#include "Game.h"
#include "Input/Input.h"

WindowData Window::s_Data;
bool Window::s_IsOpen;
float Window::s_AspectRatio = 1.0f;
float Window::s_InverseAspectRatio = 1.0f;
float Window::s_PixelSizeX = 0;
float Window::s_PixelSizeY = 0;

GLFWwindow* Window::s_Window = nullptr;

void Window::Init(){
    if(!glfwInit()){
        CORE_ERROR("Failed to initialize glfw");
        MESSAGE_BOX("GLFW API ERROR", "Failed to initialize glfw");
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    s_Window = glfwCreateWindow(s_Data.m_Width, s_Data.m_Height, "Chasmic Caverns", nullptr, nullptr);
    s_AspectRatio = (float)s_Data.m_Width / (float)s_Data.m_Height;
    s_InverseAspectRatio = (float)s_Data.m_Height / (float)s_Data.m_Width;
    s_PixelSizeX = 1.0f / (float)s_Data.m_Width;
    s_PixelSizeY = 1.0f / (float)s_Data.m_Height;

    if(!s_Window){
        CORE_ERROR("Failed to create window\n");
        MESSAGE_BOX("GLFW API ERROR", "Failed to create window");
        std::exit(-1);
    }

    glfwMakeContextCurrent(s_Window);

    GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(glfwGetPrimaryMonitor());
    s_Data.m_X = (videoMode->width - s_Data.m_Width) / 2;
    s_Data.m_Y = (videoMode->height - s_Data.m_Height) / 2;
    glfwSetWindowPos(s_Window, s_Data.m_X, s_Data.m_Y);

    glViewport(0, 0, s_Data.m_Width, s_Data.m_Height);
    if(glewInit() != GLEW_OK){
        CORE_ERROR("Failed to initialize opengl context\n");
        MESSAGE_BOX("GLEW API ERROR", "Failed to initialize glew");
        glfwTerminate();
        std::exit(-1);
    }
    glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window){
        s_IsOpen = false;
    });

    glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int width, int height){
        Window::s_Data.m_Width = width;
        Window::s_Data.m_Height = height;
        s_AspectRatio = (float)s_Data.m_Width / (float)s_Data.m_Height;
        s_InverseAspectRatio = (float)s_Data.m_Height / (float)s_Data.m_Width;
        s_PixelSizeX = 1.0f / (float)s_Data.m_Width;
        s_PixelSizeY = 1.0f / (float)s_Data.m_Height;
        glViewport(0, 0, width, height);
        Game::OnWindowResizeEvent(width, height);
    });

    glfwSetWindowPosCallback(s_Window, [](GLFWwindow* window, int xPos, int yPos){
        Window::s_Data.m_X = xPos;
        Window::s_Data.m_Y = yPos;
        Game::OnWindowPosCallback(xPos, yPos);
    });

    glfwSetKeyCallback(s_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        KeyAction keyAction;
        switch(action){
            case GLFW_REPEAT:
                keyAction = KeyAction::Repeat;
                break;
            case GLFW_RELEASE:
                keyAction = KeyAction::Release;
                break;
            case GLFW_PRESS:
                keyAction = KeyAction::Press;
                break;
        }

        unsigned char modifiers;
        if(mods & GLFW_MOD_SHIFT > 0)
            modifiers |= KeyModifierBit::LeftShift;
        Input::OnKeyEvent(key, keyAction, modifiers);
    });

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

    glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(0);
    s_IsOpen = true;
}
void Window::Shutdown(){
    glfwDestroyWindow(s_Window);
    glfwTerminate();
}
bool Window::ShouldUpdate() noexcept{return s_IsOpen;}
void Window::Close(){
    s_IsOpen = false;
}
void Window::Update(){
    glfwSwapBuffers(s_Window);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::SetBackgroundColor(float r, float g, float b){
    glClearColor(r, g, b, 1.0f);
}