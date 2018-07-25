#pragma once
#include "RingVisualization.h"
#include <stdlib.h>
#include <vector>
#include <array>
#include <stdio.h>
//Public functions:
//Default RingVisualization constructor.
RingVisualization::RingVisualization(vector<pair<float, float>>* points, vector<array<float, 4>>* colors) {
	_colors = new vector<array<float, 4>>(colors->size());
	_points = new vector<pair<float, float>>(points->size());
	_color = new GLdouble[3];
	_points->assign(points->begin(), points->end());
	_colors->assign(colors->begin(), colors->end());
}
vector<pair<float, float>> RingVisualization::getPoints() {
	return *_points;
}
vector<array<float, 4>> RingVisualization::getColors() {
	return *_colors;
}
GLdouble* RingVisualization::getColor() {
	return _color;
}
int RingVisualization::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i = 0; i < _points->size(); i++) {
		glLoadIdentity();
		glClearColor(0, 0, 0, 0);
		glColor4f((*_colors)[i][0], (*_colors)[i][1], (*_colors)[i][2], (*_colors)[i][3]);
		glFrontFace(GL_CW);
		glBegin(GL_TRIANGLE_STRIP);
			vector<pair<float, float>> *ps = new vector<pair<float, float>>(_points[i]);
			for(int j = 0; j < ps->size(); j++) {
				glVertex2f((*ps)[j].first, (*ps)[j].second);
			}
		glEnd();
	}

	glFlush();
	return 0;
}
void RingVisualization::myIdle(void) {
	glutPostRedisplay();
}
void RingVisualization::OnDraw() {
	glClear(GL_STENCIL_BUFFER_BIT);

	GLdouble quad[22][3] =
	{
		{ 5, 5, 0 },{ 15, 5, 0 },{ 15, -5, 0 },{ 5, -5, 0 },
	{ 0, 5, 0 },{ -15, 10, 0 },{ -5, -10, 0 },{ -10, 5, 0 },
	{ -0.5, 1, 0 },{ -0.5, 2, 0 },{ 0.5, 2, 0 },{ 0.5, 1, 0 }

	,{ 0.74, 0.25 },{ 0.76, 0.4 },{ 0.5, 0.75 },{ 0.1, 0.7 },{ 0.0, 0.54 },{ 0.5, 0.5 },
	{ 0, 0.5, 0 },{ -0.5, 0.1, 0 },{ -0.5, -0.1, 0 },{ -0.8, 0.5, 0 },
	};
	GLUtesselator* tess = NULL;

	tess = tesser();
	if(!tess) return;
	gluTessBeginPolygon(tess, NULL);
	gluTessBeginContour(tess);
	_color[0] = 0, _color[1] = 0.5, _color[2] = 1;
	for(int i = 12; i < 18; i++) {
		gluTessVertex(tess, quad[i], quad[i]);
	}
	gluTessEndContour(tess);
	gluTessEndPolygon(tess);

	tess = tesser();
	if(!tess) return;
	gluTessBeginPolygon(tess, NULL);
	gluTessBeginContour(tess);
	_color[0] = 1, _color[1] = 0.5, _color[2] = 0;
	for(int i = 18; i < 22; i++) {
		gluTessVertex(tess, quad[i], quad[i]);
	}
	gluTessEndContour(tess);
	gluTessEndPolygon(tess);


	for(int i = 0; i < /*(int)DrawRing::points.size()*/1; i++) { // For each partial ring
		std::vector<std::pair<float, float>> ps = RingVisualization::_points[i];
		tess = tesser();
		if(!tess) return;
		gluTessBeginPolygon(tess, NULL);
		gluTessBeginContour(tess);
		_color[0] = (*_colors)[i][0];
		_color[1] = (*_colors)[i][1];
		_color[2] = (*_colors)[i][2];

		for(int j = 0; j < (int)ps.size(); j++) {
			pt[0] = ps[j].first, pt[1] = ps[j].second, pt[2] = 0.;
			gluTessVertex(tess, pt, pt);
			printf("%.2f, %.2f\n", pt[0], pt[1]);
		}
		printf("\\\\\\\\\\\\\\\\\\\\\ \n");
		gluTessEndContour(tess);
		gluTessEndPolygon(tess);
	}

	glutSwapBuffers();
}

//Private functions:
void RingVisualization::setPoints(vector<pair<float, float>>* points) {
	this->_points->assign(points->begin(), points->end());
}
void RingVisualization::setColors(vector<array<float, 4>>* colors) {
	this->_colors->assign(colors->begin(), colors->end());
}
void CALLBACK RingVisualization::PolyLine3DBegin(GLenum type) {
	glBegin(type);
}
void CALLBACK RingVisualization::PolyLine3DVertex(GLdouble * vertex) {
	glColor3d(t->getColor()[0], t->getColor()[1], t->getColor()[2]);
	//printf("color: %.2f, %.2f, %.2f\n", color[0], color[1], color[2]);
	glVertex3dv(vertex);
}
void CALLBACK RingVisualization::PolyLine3DEnd() {
	glEnd();
}



