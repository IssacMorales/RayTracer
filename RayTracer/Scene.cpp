#include "Scene.h"
#include "MathUtils.h"
#include <iostream>
#include <iomanip>

void Scene::Render(Canvas& canvas, int numSamples, int depth)
{
    for (int y = 0; y < canvas.GetSize().y; y++)
    {
        for (int x = 0; x < canvas.GetSize().x; x++)
        {
            glm::vec2 pixel(static_cast<float>(x), static_cast<float>(y));
            glm::vec2 point = pixel / glm::vec2(canvas.GetSize());
            point.y = 1.0f - point.y;

            ray_t ray = m_camera->GetRay(point);

            raycastHit_t raycastHit;
            color3_t color = Trace(ray, 0, 100, raycastHit, depth);

            canvas.DrawPoint(pixel, color4_t(color, 1));
        }
        std::cout << std::setprecision(2) << std::setw(5) << ((y / (float)canvas.GetSize().y) * 100) << "%\n";
    }
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
    bool rayHit = false;
    float closestDistance = maxDistance;

    for (const auto& object : m_objects)
    {
        if (object->Hit(ray, minDistance, closestDistance, raycastHit))
        {
            rayHit = true;
            closestDistance = raycastHit.distance;
        }
    }

    // if ray hit object, scatter (bounce) ray and check for next hit
    if (rayHit)
    {
        ray_t scattered;
        color3_t color;

        // check if maximum depth (number of bounces) is reached, get color from material and scattered ray
        if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
        {
            // recursive function, call self and modulate (multiply) colors of depth bounces
            return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
        }
        else
        {
            // reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
            return raycastHit.material->GetEmissive();
        }
    }

    // if ray not hit, return scene sky color
    glm::vec3 direction = glm::normalize(ray.direction);
    float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
    color3_t color = lerp(m_bottomColor, m_topColor, t);

    return color;
}