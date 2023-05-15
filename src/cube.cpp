#include "cube.hpp"
#include "program.hpp"

Cube::Cube(float size)
    : m_size(size)
{
    // Calculer les coordonnées des sommets
    float x = size / 4.7f;
    float y = size / 2.0f;
    float z = size / 4.0f;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    vertices = {
        -x, -y, -z,
        x, -y, -z,
        x, y, -z,
        -x, y, -z,
        -x, -y, z,
        x, -y, z,
        x, y, z,
        -x, y, z};

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Définir les indices des triangles
    indices = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        4, 7, 6,
        6, 5, 4,
        0, 3, 7,
        7, 4, 0,
        3, 2, 6,
        6, 7, 3,
        0, 4, 5,
        5, 1, 0};

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // const GLuint VERTEX_ATTR_POSITION = 3;
    // const GLuint VERTEX_ATTR_TEXTURE  = 8;
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::draw() const
{
    //     // Chargement de la texture
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Texture->getWidth(), Texture->getHeight(),0,GL_RGBA,GL_FLOAT,texture->getPixels());

    // // Paramètres de la texture
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glBindTexture(GL_TEXTURE_2D,0);

    // Program ShaderText2D("shaders/2Dnuages.vs.glsl", "shaders/2Dnuages.fs.glsl");
    // GLuint u_txt = glGetUniformLocation(Program);

    // // Lier la texture au sampler2D dans le fragment shader
    // shader.use();
    // shader.setInt("texture1", 0);

    // // Dessiner le cube avec la texture
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // Dessiner le cube avec le VAO et l'IBO
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
