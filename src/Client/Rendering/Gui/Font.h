#pragma once

#include "pch.h"
#include "Math/Vec2.h"

#include "Rendering/Shaders/UITextShader.h"

struct GlyphCharacter {
    Vec2<float> position;   //Position into the texture
    Vec2<float> bearing;   //Position into the texture
    float ratio;
    int advance_x = 0;
    int advance_y = 0;
};

//Fonts encapsulate shaders not the other way around
//No need to have text shaders without fonts but fonts need shaders
class Font{
public:
    Font(const char* name){m_Name = name;}
    ~Font();

    void CleanUp();
    void LoadFont(const char* location);

    const char* GetName() const {return m_Name;}
    const char* GetLocation() const {return m_Location;}

    UITextShader GetShader() const{return m_Shader;}
    GLuint GetTextureId() const {return m_TextureId;}
    uint16_t GetFontSize() const {return m_FontSize;}
    GLuint GetSSBOId() const {return m_SSBO_Id;}
    GLuint GetCRDBId() const {return m_CRDB_Id;}
public:
    std::array<GlyphCharacter, 128> m_Characters;
private:
    uint16_t m_FontSize = 48;
    const char* m_Name = "font";
    const char* m_Location = "";

    UITextShader m_Shader;

    GLuint m_TextureId = 0;
    GLuint m_SSBO_Id = 0;
    GLuint m_CRDB_Id = 0;

    bool m_IsLoaded = false;
};