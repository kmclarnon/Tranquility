#ifndef _TRILLEK_TEXTURE_H_
#define _TRILLEK_TEXTURE_H_

#include "Common.h"
#include "Magick++.h"

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();
    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    Magick::Image* m_pImage;
    Magick::Blob m_blob;
};

#endif