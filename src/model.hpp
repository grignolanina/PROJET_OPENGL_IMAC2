#pragma once

#include <glimac/common.hpp>
#include "glm/fwd.hpp"
#include "light.hpp"
#include "p6/p6.h"
#include "program.hpp"
#include "textureObj.hpp"

class Model {
protected:
    GLuint m_vbo;
    GLuint m_vao;
    // GLuint m_ibo;
    // bool m_isIbo = false;
    TextureObj                       m_texture;
    std::vector<glimac::ShapeVertex> m_vertices;
    std::vector<int>                 m_index;
    GLsizei                          m_vertexCount;

public:
    /*!
     *  \brief Constructor of the Model class
     *  \param texture The texture of the model
     */
    /// \brief constructor param of the model class
    /// \param texture the texture of the model
    Model(TextureObj texture)
        : m_texture(texture)
    {}
    /// \brief default constructor
    // Model() = default;

    /// \brief cdelete model
    ~Model()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    };

    /// \brief draw the model
    void drawArray();

    /// \brief set the drawSetup
    /// \param pos position of the model
    /// \param scale scale of the model
    /// \param ProjMatrix matrice of projection for the shader
    /// \param ViewMatrix viewMatrix (camera) for the shader
    /// \param program shader will be used for drawing the model
    void draw(glm::vec3 pos, glm::vec3 scales, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Program& program);

    /// \brief get the ibo of the model
    // GLuint getIbo() const{
    //     return m_vao;
    // }

    /// \brief set and bind a vao
    void setVao();

    /// \brief set and bind vbo
    void setVbo();

    /// \brief set buffers
    void setBuffers();

    /// \brief get data
    std::vector<glimac::ShapeVertex> getData() const;

    /// \brief get data of the vertices
    const glimac::ShapeVertex* getDataPointer() const;

    /// \brief get the number of the vertices
    GLsizei getVertexCount() const
    {
        return m_vertexCount;
    }

    const int* getIndexPointer() const;

    /// \brief loader of .obj with TinyObjLoader librairy
    /// \param fileName name of the .obj
    void loadModel(const std::string& fileName);
};