#include <cstdlib>
#include "boids.hpp"
#include "glimac/common.hpp"
#include "model.hpp"
#include <iostream>
#include <vector>
#include "glimac/sphere_vertices.hpp"
#include "camera.hpp"
#include "player.hpp"
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

    GLint uKd        = glGetUniformLocation(Shader.id(), "uKd");
    GLint uKs        = glGetUniformLocation(Shader.id(), "uKs");
    GLint uShininess = glGetUniformLocation(Shader.id(), "uShininess");

    GLint uLightPos_vs    = glGetUniformLocation(Shader.id(), "uLightPos_vs");
    GLint uLightIntensity = glGetUniformLocation(Shader.id(), "uLightIntensity");

    Model perso = Model();
    Model ile = Model();
    Model boid = Model();
    perso.loadModel("perso.obj");
    ile.loadModel("ile.obj");
    boid.loadModel("oiseau.obj");

    perso.setVbo(); 
    ile.setVbo(); 
    boid.setVbo();

    perso.setVao();
    ile.setVao();
    boid.setVao();



    // GLint uTextTerre = glGetUniformLocation(Shader.id(), "uTextTerre");
    // GLint uTextMoon = glGetUniformLocation(Shader.id(), "uTextMoon");

 

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



    // const GLuint VERTEX_ATTR_POSITION = 0;
    // const GLuint VERTEX_ATTR_NORM     = 1;
    // const GLuint VERTEX_ATTR_UV       = 2;
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    // glEnableVertexAttribArray(VERTEX_ATTR_NORM);
    // glEnableVertexAttribArray(VERTEX_ATTR_UV);

    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, position)));
    // glVertexAttribPointer(VERTEX_ATTR_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, normal)));
    // glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));


    //calcul des differentes matrices necessaire pour les shaders
    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);



    Player player;
    Camera camera(player);
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;
    // bool jump = false; //pas géré




    ctx.update = [&](){
    // ctx.background(p6::NamedColor::Blue);
        
        cameraOption(camera, left, right,  up, down, ctx);
        glm::mat4 viewMatrix = camera.update();
        Shader.use();

        glClearColor(0.0f, 0.1f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., -5., -5.));
        MVMatrix = viewMatrix*MVMatrix;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


        player.drawPlayer(viewMatrix,ProjMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix, uLightPos_vs, uLightIntensity, uKs, uKd, uShininess);
        perso.draw();

        //Lumière de la scène
        glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(2, 2, 2)));
        glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(2, 2, 2)));
        glUniform1f(uShininess, 0.1);
        glUniform3fv(uLightPos_vs, 1, glm::value_ptr(glm::vec3(glm::translate(viewMatrix, glm::vec3(0, 0, -5)) * glm::vec4(1, 1, 1, 1))));
        glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(10, 10, 10)));
        //Fin lumière de la scène
    
    
        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids",&nbBoids, 0, 50, "%d", 0 );
        // ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::End();


        for(int i = 0; i<nbBoids; i++){


            boidsTab[i].drawBoid3D(ProjMatrix, NormalMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix,viewMatrix);

            boid.draw();

            // glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            boidsTab[i].updateBoid(ctx, boidsTab, sRadius, cRadius, aRadius);

        }


        //positionnement du draw de l'ile
        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0., -5., -5.));
        // MVMatrix = glm::rotate(MVMatrix, p6::Angle(90) ,glm::vec3(0, 1, 0));
        MVMatrix = glm::scale(MVMatrix, glm::vec3{5.});
        MVMatrix = viewMatrix*MVMatrix;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        ile.draw();

        
        
        //debind vao
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);



    };
    
    ctx.start();
    perso.~Model();

    

    return 0;
    

    // Should be done last. It starts the infinite loop.
    
}

// TEST_CASE("Addition is commutative")
// {
//     CHECK(1 + 2 == 2 + 1);
//     CHECK(4 + 7 == 7 + 4);
// }