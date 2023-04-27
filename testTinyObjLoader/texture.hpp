#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

#include <glimac/common.hpp>
#include <string>


class Texture {
	private:
	GLuint m_TextureId;
	std::string m_TexturePath;
	std::unique_ptr<img::Image> m_TextureImage;

	public:

	///\brief Default constructor of one texture
    Texture():m_TextureId(0), m_TexturePath(""){};


	///\brief Param constructor of one texture
	///\param texutreFile the pile path of the texture
    Texture(const std::string &textureFile):
        m_TextureId(0), 
        m_TexturePath(textureFile)
    {
        loadTexture();
    }

    ///\brief Copy constructor of one texture
	///\param texture one texture already created
    Texture(const Texture& texture):
        m_TextureId(0), 
		m_TexturePath(texture.m_TexturePath)
    {
        loadTexture();
    }


	///\brief Destructor of one texture
    ~Texture(){
        glDeleteTextures(1, &m_TextureId);
    }

	///\brief The get of the texture if
    GLuint getTextureId() const{
        return m_TextureId;
    }

	///\brief load and bind the texture
    void loadTexture(){

        *m_TextureImage = p6::load_image_buffer(m_TexturePath);

        if (m_TextureImage == nullptr){
            std::cout<<"Error, texture could not be loaded"<<std::endl; // TO DO : exception
        }

        glGenTextures(1, &m_TextureId);
        
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TextureImage->width(), m_TextureImage->height(), 0, GL_RGBA, GL_FLOAT, m_TextureImage->data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
};