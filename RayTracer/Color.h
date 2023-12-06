#pragma once
#include <glm/glm.hpp>

using color3_t = glm::vec3;

using color4_t = glm::vec4;

using rgba_t = uint32_t;

inline color4_t RGBAToColor(const rgba_t& rgba)
{
	float red = static_cast <float>((rgba >> 24) & 0xFF) / 255.0f;
	float green = static_cast <float>((rgba >> 16) & 0xFF) / 255.0f;
	float blue = static_cast <float>((rgba >> 8) & 0xFF) / 255.0f;
	float alpha = static_cast <float>(rgba >> 0xFF) / 255.0f;

	return color4_t(red, green, blue, alpha);
}

inline rgba_t ColorToRGBA(const color4_t& color)
{
	rgba_t rgba = 0;
	rgba |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24;
	rgba |= uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16;
	rgba |= uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8;
	rgba |= uint8_t(glm::clamp(color.a, 0.0f, 1.0f) * 255) << 0;

	return rgba;
}