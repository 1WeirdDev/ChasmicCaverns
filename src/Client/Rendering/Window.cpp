#include "pch.h"

#include "Core.h"
#include "Window.h"
#include "Input/Input.h"
#include "Core/Logger.h"
#include "Core/Time.h"
#include "Game.h"

WindowData Window::s_Data;
bool Window::s_IsOpen;
float Window::s_AspectRatio = 1.0f;
float Window::s_InverseAspectRatio = 1.0f;
float Window::s_PixelSizeX = 0;
float Window::s_PixelSizeY = 0;

GLFWwindow* Window::s_Window = nullptr;


void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    if(severity != GL_DEBUG_SEVERITY_HIGH)return;
    CORE_DEBUG("GL ERROR {0}, {1}, {2}, {3}, ({4})", source, type, id, severity, message);
}
void Window::Init(){
    if(!glfwInit()){
        CORE_ERROR("Failed to initialize glfw");
        MESSAGE_BOX("GLFW API ERROR", "Failed to initialize glfw");
        std::exit(-1);
    }

    //Only not resizable because of resizing stopping events
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#ifndef DIST
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Cor
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    s_Window = glfwCreateWindow(s_Data.m_Width, s_Data.m_Height, GAME_NAME, nullptr, nullptr);
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

    CORE_DEBUG("{0}", (const char*)glGetString(GL_VERSION));
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

    glfwSetCursorPosCallback(s_Window, [](GLFWwindow* window, double xPos, double yPos){
        Input::OnMouseMoveEvent(xPos, Window::s_Data.m_Height - yPos - 1);
    });

    glfwSetWindowFocusCallback(s_Window, [](GLFWwindow* window, int focused){
        if(focused == GL_FALSE){
            Input::OnWindowLostFocus();
        }
        Game::OnWindowFocusCallback(focused);
    });

    glfwSetWindowPosCallback(s_Window, [](GLFWwindow*, int xPos, int yPos){
        Game::OnWindowPosCallback(xPos, yPos);
    });

    //FUCK FRAME BUFFER RESIZE EVENTS 
    glfwSetFramebufferSizeCallback(s_Window, [](GLFWwindow* window, int width, int height){
        Time::Update();
    });
    glfwSetMouseButtonCallback(s_Window, [](GLFWwindow* window, int button, int action, int mods){
        Input::OnMouseButtonEvent(button, action == GLFW_PRESS);
    });

#ifndef DIST
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorCallback, nullptr);
#endif

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

    glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef DIST
    glfwSwapInterval(1);
#else
    glfwSwapInterval(0);
#endif
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