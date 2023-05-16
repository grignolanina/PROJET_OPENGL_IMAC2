#pragma once

#include <string>
#include "glm/fwd.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"

class TextureObj {
private:
    GLuint                      m_textureId;
    std::string                 m_textureName;
    std::unique_ptr<img::Image> m_textureImage;

public:
    // ///\brief Default constructor of one texture
    // TextureObj()
    //     : m_textureId(0), m_textureName(""){};

    ///\brief Param constructor of one texture
    ///\param textureName the pile path of the texture
    TextureObj(const std::string& textureName)
        : m_textureId(0), m_textureName(textureName)
    {
        loadTexture();
    }

    ///\brief Copy constructor of one texture
    ///\param texture one texture already created
    TextureObj(const TextureObj& texture)
        : m_textureId(0), m_textureName(texture.m_textureName)
    {
        loadTexture();
    }

    ///\brief Destructor of one texture
    ~TextureObj()
    {
        glDeleteTextures(1, &m_textureId);
    }

    ///\brief The get of the texture if
    GLuint getTextureId() const
    {
        return m_textureId;
    }

    ///\brief load and bind the texture
    void loadTexture()
    {
        *m_textureImage = p6::load_image_buffer(m_textureName);

        if (m_textureImage == nullptr)
        {
            std::cout << "Error, texture could not be loaded" << std::endl; // TO DO : exception
        }

        glGenTextures(1, &m_textureId);

        glBindTexture(GL_TEXTURE_2D, m_textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureImage->width(), m_textureImage->height(), 0, GL_RGBA, GL_FLOAT, m_textureImage->data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
};