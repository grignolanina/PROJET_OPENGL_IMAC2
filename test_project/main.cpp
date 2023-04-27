#include <cstdlib>
#include "boids.hpp"
#include "model.hpp"
#include <iostream>
#include <vector>
#include "glimac/sphere_vertices.hpp"

#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"



int main()
{
	//  { // Run the tests
    //     if (doctest::Context{}.run() != 0)
    //         return EXIT_FAILURE;
    //     // The CI does not have a GPU so it cannot run the rest of the code.
    //     const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    //     if (no_gpu_available)
    //         return EXIT_SUCCESS;
    // }
	
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    std::vector<Boid> boidsTab;
    for(int i = 0; i<50; i++){
        // Boid T = randomBoids(ctx.aspect_ratio());
        // boidsTab.push_back(T);
        boidsTab.push_back(randomBoids(ctx.aspect_ratio()));

    }

    

    //test class par default ok
    // Boid test = Boid();
    // boidsTab.push_back(test);

    // float radius = 0.02;
    float sRadius = 0.05;
    float cRadius = 0.2;
    float aRadius = 0.1;
    int nbBoids = 20;

    //load shaders
    // p6::Shader Shader = p6::load_shader("shaders/3D.vs.glsl", "shaders/normal.fs.glsl");
    p6::Shader Shader = p6::load_shader("shaders/3Dboids.vs.glsl", "shaders/3Dboids.fs.glsl");

    // //load texture
    // img::Image img_terre = p6::load_image_buffer("assets/textures/EarthMap.jpg");
    // img::Image img_lune = p6::load_image_buffer("assets/textures/MoonMap.jpg");

    //recup variable uniforme
    GLint uMVPMatrix    = glGetUniformLocation(Shader.id(), "uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(Shader.id(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(Shader.id(), "uNormalMatrix");

    Model perso = Model();
    perso.loadModel("personnage.obj");
    
    perso.setVbo();

    perso.setVao();



    // GLint uTextTerre = glGetUniformLocation(Shader.id(), "uTextTerre");
    // GLint uTextMoon = glGetUniformLocation(Shader.id(), "uTextMoon");

    //creation du vbo
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //creation de la shape
    const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);
    // const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(test., this->m_pos.x, m_pos.y);


    // fill those coords in the vbo / Static is for constant variables
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    //oprion pour voir les tests en profondeur?
    glEnable(GL_DEPTH_TEST);


    //initialisation de textures
    // GLuint textureTerre;
    // glGenTextures(1, &textureTerre);
    // glBindTexture(GL_TEXTURE_2D, textureTerre);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_terre.width(), img_terre.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_terre.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);
    
    // GLuint textureMoon;
    // glGenTextures(1, &textureMoon);
    // glBindTexture(GL_TEXTURE_2D, textureMoon);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_lune.width(), img_lune.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_lune.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);  

    // creation du vao
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORM     = 1;
    const GLuint VERTEX_ATTR_UV       = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORM);
    glEnableVertexAttribArray(VERTEX_ATTR_UV);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));

    // debind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // debind du vao
    glBindVertexArray(0);

    //calcul des differentes matrices necessaire pour les shaders
    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    


    //axe de rotation aléatoire lune
    // std::vector<glm::vec3> angleRotation;
    // std::vector<glm::vec3> axeTranslation;

    // for(int i = 0; i<32; i++){
    //     angleRotation.push_back(glm::sphericalRand(2.f));
    //     axeTranslation.push_back(glm::sphericalRand(2.f));
    // }




    ctx.update = [&](){
    ctx.background(p6::NamedColor::Black);

        Shader.use();
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind vao
        glBindVertexArray(vao);

        //bind texture terre
        // glBindTexture(GL_TEXTURE_2D, textureTerre);

        // //TERRE
        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., 0., -5.));
        MVMatrix = glm::rotate(MVMatrix, -ctx.time(), glm::vec3(0, 1, 0));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // //mise en place texture terre
        // // glUniform1i(uTextTerre,0);

        // //application de met matrice dans les shaders
        // glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        // glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        // glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        //draw le vertice
        

        // glBindTexture(GL_TEXTURE_2D, textureMoon);


        // //LUNES
        // for(int i = 0; i<32; i++){
        //     // glUniform1i(uTextMoon,0);
        //     //creation d'une nouvelle mv pour la moon
        //     glm::mat4 MVMatrixMoon = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f}); // Translation
        //     MVMatrixMoon = glm::rotate(MVMatrixMoon, ctx.time(), angleRotation[i]); // Translation * Rotation
        //     MVMatrixMoon = glm::translate(MVMatrixMoon, axeTranslation[i]); // Translation * Rotation * Translation
        //     MVMatrixMoon = glm::scale(MVMatrixMoon, glm::vec3{0.2f}); // Translation * Rotation * Translation * Scale

        //     glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrixMoon));
        //     glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixMoon));
        //     glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        //     glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        // }
        


        // glActiveTexture(GL_TEXTURE0);
    
        


        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids",&nbBoids, 0, 51, "%.3f", 0 );
        // ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::End();


        for(int i = 0; i<nbBoids; i++){
            // boidsTab[i].drawBoid(ctx);
            // glDrawArrays(GL_TRIANGLES, 0, vertices.size());

                        //creation d'une nouvelle mv pour la moon
            // glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f}); // Translation
            // MVMatrixBoids = glm::rotate(MVMatrixBoids, ctx.time(), glm::normalize(boidsTab[i].randomSpeed())); // Translation * Rotation
            // MVMatrixBoids = glm::translate(MVMatrixBoids, boidsTab[i].randomPos(ctx.aspect_ratio())); // Translation * Rotation * Translation
            // MVMatrixBoids = glm::scale(MVMatrixBoids, glm::vec3{0.2f}); // Translation * Rotation * Translation * Scale

            // glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrixBoids));
            // glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixBoids));
            // glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

            boidsTab[i].drawBoid3D(ProjMatrix, NormalMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            boidsTab[i].updateBoid(ctx, boidsTab, sRadius, cRadius, aRadius);

        }

        
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        perso.draw();

        
        
        //debind vao
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    };
    
    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    perso.~Model();
    // glDeleteTextures(1, &textureTerre);
    // glDeleteTextures(1, &textureMoon);

    

    return 0;
    

    // Should be done last. It starts the infinite loop.
    
}

// TEST_CASE("Addition is commutative")
// {
//     CHECK(1 + 2 == 2 + 1);
//     CHECK(4 + 7 == 7 + 4);
// }