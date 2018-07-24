#pragma once
#include "RingVisualization.h"

//Public functions:
//Default RingVisualization constructor.
RingVisualization::RingVisualization(vector<pair<float, float>>* points, vector<array<float, 4>>* colors) {
	_colors = new vector<array<float, 4>>(colors->size());
	_points = new vector<pair<float, float>>(points->size());
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
void CALLBACK RingVisualization::(GLdouble * vertex) {
	glColor3d(RingVisualization::getColor(), _color[1], _color[2]);
	//printf("color: %.2f, %.2f, %.2f\n", color[0], color[1], color[2]);
	glVertex3dv(vertex);
}
void CALLBACK RingVisualization::PolyLine3DEnd() {
	glEnd();
}



