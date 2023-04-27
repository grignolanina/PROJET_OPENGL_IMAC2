#include <cstdlib>
#include "boids.hpp"
#include "model.hpp"
#include <iostream>
#include <vector>
#include "glimac/common.hpp"
#include "glimac/sphere_vertices.hpp"
#include "tiny_obj_loader.h"

#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"



int main()
{	
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    //load shaders
    p6::Shader Shader = p6::load_shader("shaders/objText.vs.glsl", "shaders/objText.fs.glsl");

    //recup variable uniforme
    GLint uMVPMatrix    = glGetUniformLocation(Shader.id(), "uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(Shader.id(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(Shader.id(), "uNormalMatrix");

    GLint uTextIle = glGetUniformLocation(Shader.id(), "uTextIle");

    // img::Image img_ile = p6::load_image_buffer("assets/textures/ile.png");

    Texture ileTxt = Texture("assets/textures/ile.png");



    Model ile = Model(ileTxt);
    ile.loadModel("ile.obj");
    ile.setVbo();


    //oprion pour voir les tests en profondeur?
    glEnable(GL_DEPTH_TEST);

    // GLuint textureIle;
    // glGenTextures(1, &textureIle);
    // glActiveTexture(GL_TEXTURE0); // la texture textureTerre est bindée sur l'unité GL_TEXTURE0
    // glBindTexture(GL_TEXTURE_2D, textureIle);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_ile.width(), img_ile.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_ile.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // //debind text
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);


    ile.setVao();

    //calcul des differentes matrices necessaire pour les shaders
    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);



    ctx.update = [&](){
    ctx.background(p6::NamedColor::Black);

        Shader.use();
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind vao
        // glBindVertexArray(vao);
        glUniform1i(uTextIle, 0);


        // //TERRE
        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., -2., -5.));
        // MVMatrix = glm::rotate(MVMatrix, -ctx.time(), glm::vec3(0, 1, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textureIle);

        ile.draw();

        
        //debind vao
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    };
    
    ctx.start();

    // glDeleteTextures(1, &textureIle);


    

    return 0;
    

    
}