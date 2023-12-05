#pragma once
#include "Ray.h"
#include "Color.h"
#include "Random.h"
#include "MathUtils.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : m_albedo(albedo) {}
	
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;

private:
	color3_t CalculatedGradientColor(float distance) const;

private:
	float maxDistance_ = 100.0f;
	color3_t m_albedo;
};

class Metal : public Material
{
public:
	Metal(const color3_t& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;
	
protected:
	glm::vec3 m_albedo{ 0 };
	float m_fuzz{ 0 };
};