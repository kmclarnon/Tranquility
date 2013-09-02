#ifndef _TRILLEK_TEXTURE_H_
#define _TRILLEK_TEXTURE_H_

#include "Common.h"

#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 4244)
#include "Magick++.h"
#pragma warning(pop)

class Texture
{
public:
    Texture(GLenum textureTarget, const std::string& fileName);

    bool load();
    void bind(GLenum TextureUnit) const;

private:
    std::string fileName;
    GLenum textureTarget;
    GLuint textureObj;
    std::unique_ptr<Magick::Image> image;
    Magick::Blob blob;
};

#endif