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




    // float radius = 0.02;
    float sRadius = 0.05;
    float cRadius = 0.2;
    float aRadius = 0.1;
    int nbBoids = 20;

    //load shaders
    p6::Shader Shader = p6::load_shader("shaders/3Dboids.vs.glsl", "shaders/3Dboids.fs.glsl");

    //recup variable uniforme
    GLint uMVPMatrix    = glGetUniformLocation(Shader.id(), "uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(Shader.id(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(Shader.id(), "uNormalMatrix");

    Model perso = Model();
    perso.loadModel("personnage.obj");
    perso.setVbo();


    //oprion pour voir les tests en profondeur?
    glEnable(GL_DEPTH_TEST);


    perso.setVao();

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

        // //TERRE
        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., 0., -5.));
        MVMatrix = glm::rotate(MVMatrix, -ctx.time(), glm::vec3(0, 1, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids",&nbBoids, 0, 51, "%.3f", 0 );
        // ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::End();


        // for(int i = 0; i<nbBoids; i++){

        //     boidsTab[i].drawBoid3D(ProjMatrix, NormalMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix);

        //     glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        //     boidsTab[i].updateBoid(ctx, boidsTab, sRadius, cRadius, aRadius);
        // }

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        perso.draw();

        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., -2., -5.));
        MVMatrix = glm::rotate(MVMatrix, -ctx.time(), glm::vec3(0, 1, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

         glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        // perso2.draw();


        // glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        
        //debind vao
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    };
    
    ctx.start();

    

    return 0;
    

    
}