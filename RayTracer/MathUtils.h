#pragma once

#include <glm/glm.hpp>

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

// Dot product function
inline float dot(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::dot(v1, v2);
}

//refleciton
inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
    return glm::reflect(v, n);
}

//approximately
inline bool approximately(float value1, float value2)
{
    // check if the absolute difference between the values is less than epsilon
    return (std::abs(value1 - value2) < FLT_EPSILON);
}