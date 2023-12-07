#pragma once
#include "Object.h"

class Plane : public Object
{
public:
    Plane() = default;
    Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
        Object(material), // Assuming Object has a constructor that takes a material
        m_center(center),
        m_normal(normal)
    {
    }

    bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
    glm::vec3 m_center{ 0.0f, 0.0f, 0.0f }; // Center of the plane
    glm::vec3 m_normal{ 0.0f, 1.0f, 0.0f }; // Normal vector of the plane (default: pointing upward)
};
