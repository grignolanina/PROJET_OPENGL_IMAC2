// #pragma once
// #include <glimac/common.hpp>
// #include "glm/fwd.hpp"
// #include "img/src/Image.h"
// #include "p6/p6.h"

// class TextureObj {
// private:
//     GLuint     m_textName;
//     img::Image m_imgObjet;

// public:
//     TextureObj(GLuint textName, img::Image& imgObjet)
//         : m_textName(textName), m_imgObjet((imgObjet)){};
//     void configTex()
//     {
//         glGenTextures(1, &this->m_textName);
//         glBindTexture(GL_TEXTURE_2D, this->m_textName);

//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_imgObjet.width(), this->m_imgObjet.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->m_imgObjet.data());
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//         glBindTexture(GL_TEXTURE_2D, 0);
//     }

//     GLuint getTextName()
//     {
//         return this->m_textName;
//     }
// };