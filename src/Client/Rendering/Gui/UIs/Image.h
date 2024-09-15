#pragma once

#include "../UI.h"

class Image : public UI{
public:
    Image() {m_UIType = UT_Image; }
    Image(GLuint texture){m_UIType = UT_Image; m_TextureId = texture;}
    ~Image(){DeleteChildren();}
    
    void SetTextureId(GLuint texture){m_TextureId = texture;}
    GLuint GetTextureId() const {return m_TextureId;}
private:
    GLuint m_TextureId = 0;
};