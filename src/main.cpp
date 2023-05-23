#include <cstdlib>
#include <iostream>
#include <vector>
#include "boids/boids.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "glimac/common.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "img/src/Image.h"
#include "light.hpp"
#include "model.hpp"
#include "obstacle.hpp"
#include "p6/p6.h"
#include "program.hpp"
#include "texture.hpp"

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

    auto ctx = p6::Context{{1280, 720, "GAME"}};
    ctx.maximize_window();

    std::vector<Boid> boidsTab;
    for (int i = 0; i < 50; i++)
    {
        // Boid T = randomBoids(ctx.aspect_ratio());
        // boidsTab.push_back(T);
        boidsTab.push_back(randomBoids(ctx.aspect_ratio()));
    }

    // float radius = 0.02;
    float sRadius = 0.05;
    float cRadius = 0.2;
    float aRadius = 0.1;
    int   nbBoids = 20;

    //  //nouveau set
    Program ShaderPoint("shaders/3D.vs.glsl", "shaders/multiplePointLight.fs.glsl");
    // Program ShaderText("shaders/3D.vs.glsl", "shaders/3Dboids.fs.glsl");
    Program ShaderCube("shaders/2Dnuages.vs.glsl", "shaders/2Dnuages.fs.glsl");

    img::Image Texture    = p6::load_image_buffer("assets/textures/nuages.jpg");
    img::Image img_ile    = p6::load_image_buffer("assets/textures/textureIleBlake.png");
    img::Image img_perso  = p6::load_image_buffer("assets/textures/persoBake.jpg");
    img::Image img_oiseau = p6::load_image_buffer("assets/textures/oiseauBake.jpg");

    ShaderPoint.addUniformVariable("uMVPMatrix");
    ShaderPoint.addUniformVariable("uMVMatrix");
    ShaderPoint.addUniformVariable("uNormalMatrix");
    ShaderPoint.addUniformVariable("uKd");
    ShaderPoint.addUniformVariable("uKs");
    ShaderPoint.addUniformVariable("uShininess");
    ShaderPoint.addUniformVariable("uLightPos_vs");
    ShaderPoint.addUniformVariable("uLightIntensity");
    ShaderPoint.addUniformVariable("uLightPos2_vs");
    ShaderPoint.addUniformVariable("uLightIntensity2");
    ShaderPoint.addUniformVariable("uText");

    // ShaderText.addUniformVariable("uMVPMatrix");
    // ShaderText.addUniformVariable("uMVMatrix");
    // ShaderText.addUniformVariable("uNormalMatrix");

    ShaderCube.addUniformVariable("uTexture");
    ShaderCube.addUniformVariable("uMVPMatrix");
    ShaderCube.addUniformVariable("uMVMatrix");
    ShaderCube.addUniformVariable("uNormalMatrix");

    Model perso = Model();
    Model ile   = Model();
    Model boid  = Model();
    perso.loadModel("persoBake.obj");
    ile.loadModel("ileBake.obj");
    boid.loadModel("oiseauBake.obj");

    GLuint persoBake;

    // TextureObj textPerso(persoBake, img_perso);
    // textPerso.configTex();

    glGenTextures(1, &persoBake);
    glBindTexture(GL_TEXTURE_2D, persoBake);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_perso.width(), img_perso.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_perso.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint oiseauBake;
    glGenTextures(1, &oiseauBake);
    glBindTexture(GL_TEXTURE_2D, oiseauBake);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_oiseau.width(), img_oiseau.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_oiseau.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint ileBake;
    glGenTextures(1, &ileBake);
    glBindTexture(GL_TEXTURE_2D, ileBake);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_ile.width(), img_ile.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_ile.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    perso.setVbo();
    ile.setVbo();
    boid.setVbo();

    perso.setVao();
    ile.setVao();
    boid.setVao();
    Cube cube(5.0f);
    cube.init(Texture);


    glEnable(GL_DEPTH_TEST);

    // calcul des differentes matrices necessaire pour les shaders
    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);

    Player player;
    Camera camera(player, perso);
    bool   right = false;
    bool   left  = false;
    bool   up    = false;
    bool   down  = false;

    glm::vec3 obstaclePosition(0.0f, -5.0f, -2.0f);
    float     obstacleSize = 0.5f;
    Obstacle  obstacle(obstaclePosition, obstacleSize);
    glm::vec3 playerPosition = player.getPosition();

    // bool jump = false; //pas géré

    Light lightScene = Light(glm::vec3{100.});
    Light lightPerso = Light(glm::vec3{0.0001});
    ctx.update       = [&]() {
        // ctx.background(p6::NamedColor::Blue);

        cameraOption(player, left, right, up, down, ctx);
        glm::mat4 viewMatrix = player.getViewMatrix();

        camera.update(viewMatrix);

        ShaderPoint.use();

        glClearColor(0.0f, 0.1f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MVMatrix     = glm::translate(glm::mat4(1.0), glm::vec3(0., -5., -5.));
        MVMatrix     = viewMatrix * MVMatrix;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        lightScene.drawLightScene(glm::vec3(0., 5., -5.), ProjMatrix, viewMatrix, ShaderPoint);
        lightPerso.drawLightPlayer(player.getPosition(), ProjMatrix, viewMatrix, ShaderPoint);

        player.drawPlayer(perso, viewMatrix, ProjMatrix, ShaderPoint, persoBake);

        ile.draw(glm::vec3(0., -5., -5.), glm::vec3{5.}, ProjMatrix, viewMatrix, ShaderPoint, ileBake);

        ShaderCube.use();
        cube.draw(glm::vec3(0., -5., -5.), glm::vec3{5.}, ShaderCube, viewMatrix, ProjMatrix);
        cube.borders(player);
        obstacle.avoid(playerPosition);

        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids", &nbBoids, 0, 50, "%d", 0);
        // ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0);
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0);
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0);
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0);
        ImGui::End();

        ShaderPoint.use();

        for (int i = 0; i < nbBoids; i++)
        {
            boidsTab[i].drawBoid3D(boid, ProjMatrix, NormalMatrix, viewMatrix, ShaderPoint, oiseauBake);

            boidsTab[i].updateBoid(ctx, boidsTab, sRadius, cRadius, aRadius);
        }
    };

    ctx.start();
    perso.~Model();
    ile.~Model();
    boid.~Model();

    return 0;
}