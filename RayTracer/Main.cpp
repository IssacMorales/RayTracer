#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"  // Include the Scene header file
#include "Camera.h" // Include the Camera header file

#include <iostream>

int main(int, char**)
{
    Renderer renderer;

    if (!renderer.Initialize() || !renderer.CreateWindow("My Window", 800, 600))
    {
        std::cerr << "Failed to initialize renderer." << std::endl;
        return 1;
    }

    Canvas canvas(800, 600, renderer);

    // Create Camera
    float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

    // Create Scene
    Scene scene(glm::vec3{ 0.5, 0.7, 1 }, glm::vec3{ 0.1, 0.1, 0.1 }); // Set top and bottom colors

    scene.SetCamera(camera);

    while (true)
    {
        scene.Render(canvas);

        canvas.Update();
        renderer.PresentCanvas(canvas);
    }

    return 0;
}