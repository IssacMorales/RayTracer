#include "Ray.h"
#include "Scene.h"
#include "MathUtils.h"

void Scene::Render(Canvas& canvas)
{
    for (int y = 0; y < canvas.GetSize().y; y++)
    {
        for (int x = 0; x < canvas.GetSize().x; x++)
        {
            glm::vec2 pixel(static_cast<float>(x), static_cast<float>(y));
            glm::vec2 point = pixel / glm::vec2(canvas.GetSize());
            point.y = 1.0f - point.y;

            ray_t ray = m_camera->GetRay(point);

            color3_t color = Trace(ray);

            canvas.DrawPoint(pixel, color4_t(color, 1));
        }
    }
}

color3_t Scene::Trace(const ray_t& ray)
{
    glm::vec3 direction = glm::normalize(ray.direction);

    // set scene sky color
    float t = (direction.y + 1) * 0.5f;
    color3_t color = lerp(m_bottomColor, m_topColor, t);

    return color;
}