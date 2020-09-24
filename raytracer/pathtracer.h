#pragma once
#include "type.h"
#include "screen.h"
#include "scene.h"
#include "primitive.h"

class pathtracer {
public:
	void render(const scene &sc, screen &scrn);
private:
	vector3f trace(ray r, int depth);
private: //material
	vector3f light(const ray &r, const hit &h, int depth);
	vector3f diffuse(const ray &r, const hit &h, int depth);
	vector3f specular(const ray &r, const hit &h, int depth);
	vector3f glass(const ray &r, const hit &h, int depth);
	vector3f glossy(const ray &r, const hit &h, int depth);
private:
	float pdf(const material *m, const vector3f &wi,
		const vector3f &wo, const vector3f &N);
	float brdf(const material *m, const vector3f &wi,
		const vector3f &wo, const vector3f &N);
	vector3f sample_uniform(const material *m,
		const vector3f &wo, const vector3f &N);
private:
	float fov = 40;
	const scene *sc = nullptr;
	const screen *scrn = nullptr;
	vector3f eye_pos = vector3f(278,273,-800);
	vector3f background = vector3f(0.235294, 0.67451, 0.843137);
};
