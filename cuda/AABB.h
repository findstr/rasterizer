#pragma once
#include <iostream>
#include "type.h"
#include "ray.h"

namespace render {

struct AABB2f {
	vector2f min;
	vector2f max;
	CPU AABB2f() {
		float inf = INFINITY;
		min = vector2f(inf, inf);
		max = vector2f(-inf, -inf);
	}
	template<typename T> CPU void extend(const T &v) {
		for (int i = 0; i < 2; i++) {
			min[i] = fminf(min[i], v[i]);
			max[i] = fmaxf(max[i], v[i]);
		}
	}
};

struct AABB3f {
	vector3f min;
	vector3f max;
	CPU AABB3f() {
		float inf = INFINITY;
		min = vector3f(inf, inf, inf);
		max = vector3f(-inf, -inf, -inf);
	}
	template<typename T> CPU void extend(const T &v) {
		for (int i = 0; i < 3; i++) {
			min[i] = fminf(min[i], v[i]);
			max[i] = fmaxf(max[i], v[i]);
		}
	}
	GPU bool intersect(const ray &r) const {
		float t_min, t_max;
		vector3f rmin, rmax;
		float inf = INFINITY;
		rmax = vector3f(inf, inf, inf);
		rmin = vector3f(-inf, -inf, -inf);
		auto &origin = r.origin;
		auto &dir = r.direction;
		for (int i = 0; i < 3; i++) {
			auto d = dir[i];
			if (d != 0) {
				rmin[i] = (min[i] - origin[i]) / d;
				rmax[i] = (max[i] - origin[i]) / d;
				if (d < 0)
					std_swap(rmin[i], rmax[i]);
			}
		}
		t_min = fmaxf(fmaxf(rmin[0], rmin[1]), rmin[2]);
		t_max = fminf(fminf(rmax[0], rmax[1]), rmax[2]);
		return t_min <= t_max && t_max >= 0;
	}
};

}
