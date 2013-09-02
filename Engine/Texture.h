#ifndef _TRILLEK_TEXTURE_H_
#define _TRILLEK_TEXTURE_H_

#include "Common.h"
#include "Magick++.h"

class Texture
{
public:
    Texture(GLenum textureTarget, const std::string& fileName);

    bool Load();
    void Bind(GLenum TextureUnit) const;

private:
    std::string fileName;
    GLenum textureTarget;
    GLuint textureObj;
    std::unique_ptr<Magick::Image> image;
    Magick::Blob blob;
};

#endif