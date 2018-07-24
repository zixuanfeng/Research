//Amended by Josiah
#ifndef _GEN_POINT_H
#define _GEN_POINT_H

#include <vector>
#include <utility>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

class GeneratePartRingPoints {
private:
	// The inner (small) radius
	float r1;

	// The outter (larger) radius
	float r2;

	// The start and end angle of ring in radian (counter clockwise)
	float start_angle, end_angle;

	// The number of points
	int n;

	// Series of points (x,y) for the partial ring
	std::vector<std::pair<float, float>> points;
	// Generate points for polygon representation of the ring
	int generate_points();
	
public:
	GeneratePartRingPoints(int n, float r1, float r2, float startangle, float endangle) :
	n(n), r1(r1), r2(r2), start_angle(startangle), end_angle(endangle){ }

	// Get all points for the paritial ring
	int getPoints(std::vector<std::pair<float, float>> &);

	void generatePartRingPoints();
};

void GeneratePartRingPoints::generatePartRingPoints() {
	this->generate_points();
}

int GeneratePartRingPoints::getPoints(std::vector<std::pair<float, float>> &ps) {
	ps.clear();
	ps.assign(this->points.begin(), this->points.end());
	return this->points.size();
}

int GeneratePartRingPoints::generate_points() {
	/*float r = r1;
	float dr = (r2 - r1) / (n / 8.f);
	for (int i = 0; i < n / 8; i++) {
		r += dr;
		this->points.push_back(std::pair<float, float>(r*std::cos(start_angle), r*std::sin(start_angle)));
	}

	float angle = start_angle;
	float dangle = (end_angle - start_angle) / (n * 3.f / 8.f);
	for (int i = 0; i < n*3 / 8; i++) {
		angle += dangle;
		this->points.push_back(std::pair<float, float>(r2*std::cos(angle), r2*std::sin(angle)));
	}

	r = r2;
	for (int i = 0; i < n / 8; i++) {
		r -= dr;
		this->points.push_back(std::pair<float, float>(r*std::cos(end_angle), r*std::sin(end_angle)));
	}

	angle = end_angle;
	for (int i = 0; i < 3 * n / 8; i++) {
		angle -= dangle;
		this->points.push_back(std::pair<float, float>(r1*std::cos(angle), r1*std::sin(angle)));
	}*/
	
	float dangle = (end_angle - start_angle) / n;
	float angle = end_angle;
	//printf("start angle: %.2f end angle: %.2f delta angle: %.2f r1 %.2f r2 %.2f\n", start_angle, end_angle, dangle, r1, r2);
	for (int i = 0; i < n; i++) {
		angle -= dangle;
		//printf("angle: %.2f\n", angle);
		this->points.push_back(std::pair<float, float>(r1*cos(angle), r1*sin(angle)));
		this->points.push_back(std::pair<float, float>(r2*cos(angle), r2*sin(angle)));
	}

	return n;
}

#endif