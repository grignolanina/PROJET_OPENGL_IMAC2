#include <stdlib.h>
#include "boids.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
// #define DOCTEST_CONFIG_IMPLEMENT
// #include "doctest/doctest.h"
#include <vector>

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

    // std::vector<Boid> boidsTab;
    // for(int i = 0; i<50; i++){
    //     Boid T(ctx.aspect_ratio());
    //     boidsTab.push_back(T);
    // }
    std::vector<Boid> boidsTab;
    for(int i = 0; i<50; i++){
        // Boid T = randomBoids(ctx.aspect_ratio());
        // boidsTab.push_back(T);
        boidsTab.push_back(randomBoids(ctx.aspect_ratio()));

    }

    //test class par default ok
    Boid test = Boid();
    boidsTab.push_back(test);

    // float radius = 0.02;
    float sRadius = 0.05;
    float cRadius = 0.2;
    float aRadius = 0.1;
    int nbBoids = 20;


    ctx.update = [&](){
        ctx.background(p6::NamedColor::Black);

        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids",&nbBoids, 0, 51, "%.3f", 0 );
        // ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::End();


        for(int i = 0; i<nbBoids; i++){
            boidsTab[i].drawBoid(ctx);
            boidsTab[i].updateBoid(ctx, boidsTab, sRadius, cRadius, aRadius);
        }   
    };


    

    


    

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

// TEST_CASE("Addition is commutative")
// {
//     CHECK(1 + 2 == 2 + 1);
//     CHECK(4 + 7 == 7 + 4);
// }