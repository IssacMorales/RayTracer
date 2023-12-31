#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Random.h"
#include "Plane.h"
#include "Triangle.h"
#include "Color.h"
#include "Mesh.h"
 
#include <iostream>
#include <vector>
 
int main(int, char**) {
    Renderer renderer;

    const int width = 400;
    const int height = 300;
    const int samples = 20;
    const int depth = 5;
 
    // Create material with a specific max distance
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
 
    if (!renderer.Initialize() || !renderer.CreateWindow("Way Twaco", width, height)) {
        std::cerr << "Failed to initialize renderer." << std::endl;
        return 1;
    }
 
    Canvas canvas(width, height, renderer); // Adjusted canvas size
 
    // Create Camera
    float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
 
    // Create Scene with depth
    Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

    void InitScene01(Scene & scene, const Canvas & canvas);
    void InitScene02(Scene & scene, const Canvas & canvas);

    //InitScene01(scene, canvas);
    InitScene02(scene, canvas);

    scene.SetCamera(camera);
 
    // Add spheres to the scene using a loop
    /*std::vector<glm::vec3> spherePositions;
    int numSpheres = 20;
 
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {

            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::vec3{ random(0, 360), 1.0f, 1.0f });
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f;

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }*/

    //add a plane
    material = std::make_shared<Lambertian>(color3_t{ 0.2f });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));

    // Create a Triangle
    /*auto triangleMaterial = std::make_shared<Lambertian>(color3_t{ 2.0f, 2.0f, 2.0f });
    auto triangle = std::make_unique<Triangle>(glm::vec3{ 1, 0, -5 }, glm::vec3{ 0, 1, -5 }, glm::vec3{ -1, 0, -5 }, triangleMaterial);
    scene.AddObject(std::move(triangle));*/

    //add mesh
    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 1.0f, 0 }, glm::vec3{ 0, 1, 0 });
    scene.AddObject(std::move(mesh));


    // Main rendering loop
    while (true) {
        // Render scene 
        canvas.Clear({ 0, 0, 0, 1 });
        scene.Render(canvas, samples, depth);
        canvas.Update();
        renderer.PresentCanvas(canvas);
 
        // Handle events and input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                // Exit the loop when the window is closed
                return 0;
            }
        }
    }
}

//new scene stuff
void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // create objects -> add to scene
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {
            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::vec3{ random(0, 360), 1.0f, 1.0f });
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f;

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    //auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    //scene.AddObject(std::move(triangle));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));

    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));
}