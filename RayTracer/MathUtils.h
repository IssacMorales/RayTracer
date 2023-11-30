#pragma once

// Cross product function
inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

// Linear interpolation function
template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
    return (a * (1 - t)) + (b * t);
}