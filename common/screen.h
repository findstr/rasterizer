#pragma once
#include "type.h"
#include "auxiliary.h"
#include <opencv2/opencv.hpp>

class screen {
public:
	screen(int w, int h) {
		size.x() = w;
		size.y() = h;
		framebuf.resize(w*h);
		depthbuf.resize(w*h);
		clear();
	}
	float aspect() {
		return (float)size.x() / (float)size.y();
	}
	void clear() {
		scale_ = 1.f;
		vector3f ZERO(0, 0, 0);
		auto INF = std::numeric_limits<float>::infinity();
		std::fill(framebuf.begin(), framebuf.end(), ZERO);
		std::fill(depthbuf.begin(), depthbuf.end(), INF);
	}
	bool ztest(int x, int y, float z) {
		if (x < 0 || y < 0)
			return false;
		unsigned idx = x + size.x() * (size.y() - y - 1);
		if (idx >= depthbuf.size())
			return false;
		return depthbuf[idx] > z;
	}
	void zset(int x, int y, float depth) {
		if (x < 0 || y < 0)
			return ;
		int idx = x + size.x() * (size.y() - y - 1);
		depthbuf[idx] = depth;
	}
	void set(int x, int y, const vector3f &color) {
		if (x < 0 || y < 0)
			return ;
		int idx = x + size.x() * (size.y() - y - 1);
		framebuf[idx] = color;
	}
	void scale(float s) {
		scale_ = s;
	}
	void add(int x, int y, const vector3f &color) {
		if (x < 0 || y < 0)
			return ;
		int idx = x + size.x() * (size.y() - y - 1);
		framebuf[idx] += color;
	}

	void dump(const char *name) {
		FILE* fp = fopen(name, "wb");
		fprintf(fp, "P6\n%d %d\n255\n", size.x(), size.y());
		for (int i = 0; i < size.x() * size.y(); i++) {
			unsigned char color[3];
			vector3f &c = framebuf[i];
			color[0] = (unsigned char)(255.f * std::pow(clamp(c.x() * scale_), 1.f/2.2f));
			color[1] = (unsigned char)(255.f * std::pow(clamp(c.y() * scale_), 1.f/2.2f));
			color[2] = (unsigned char)(255.f * std::pow(clamp(c.z() * scale_), 1.f/2.2f));
			fwrite(color, 1, 3, fp);
		}
		fclose(fp);
	}
	void show() {
		auto tmp = framebuf;
		for (int i = 0; i < size.x() * size.y(); i++) {
			vector3f &c = tmp[i];
			c.x() = (unsigned char)(255.f * std::pow(clamp(c.x() * scale_), 1.f/2.2f));
			c.y() = (unsigned char)(255.f * std::pow(clamp(c.y() * scale_), 1.f/2.2f));
			c.z() = (unsigned char)(255.f * std::pow(clamp(c.z() * scale_), 1.f/2.2f));
		}
		std::string filename = "output.png";
		cv::Mat image(size.x(), size.y(), CV_32FC3, tmp.data());
		image.convertTo(image, CV_8UC3, 1.f);
		cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
		cv::imshow("image", image);
	}
	const vector2i &getsize() const {
		return size;
	}
private:
	float scale_;
	vector2i size;
	std::vector<float> depthbuf;
	std::vector<vector3f> framebuf;
};
