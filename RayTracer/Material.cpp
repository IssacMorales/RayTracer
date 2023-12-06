#include "Material.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
{
	glm::vec3 target = raycastHit.point + raycastHit.normal + RandomInUnitSphere();
	glm::vec3 direction = glm::normalize(target - raycastHit.point);

	scattered = ray_t(raycastHit.point, direction);
	color = m_albedo * CalculatedGradientColor(raycastHit.distance);

	return true;
}

color3_t Lambertian::CalculatedGradientColor(float distance) const
{
	float t = distance / maxDistance_;
	t = glm::smoothstep(0.0f, 1.0f, t);
	return lerp(color3_t{ 0,0,1 }, color3_t{ 0,0,0 }, t);
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
{
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);

	scattered = ray_t(raycastHit.point, reflected + m_fuzz * RandomInUnitSphere());
	color = m_albedo;

	return glm::dot(scattered.direction, raycastHit.normal) > 0;
}