#include "Texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName) : textureTarget(TextureTarget), fileName(FileName)
{
    textureTarget = TextureTarget;
    fileName      = FileName;
    image        = NULL;
}

bool Texture::load()
{
    try 
    {
        image = std::unique_ptr<Magick::Image>(new Magick::Image(fileName));
        image->write(&this->blob, "RGBA");
    }
    catch (Magick::Error& Error) 
    {
        std::cout << "Error loading texture '" << fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &this->textureObj);
    glBindTexture(this->textureTarget, this->textureObj);
    glTexImage2D(this->textureTarget, 0, GL_RGB, this->image->columns(), this->image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->blob.data());
    glTexParameterf(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::bind(GLenum TextureUnit) const
{
    glActiveTexture(TextureUnit);
    glBindTexture(this->textureTarget, this->textureObj);
}