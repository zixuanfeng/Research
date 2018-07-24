//Amended by Josiah
#ifndef _DRAW_RING_H
#define _DRAW_RING_H

#include <vector>
#include <utility>
#include <algorithm>
#include <gl/glut.h>

class DrawRing {
private:
	static std::vector<std::vector<float>> colors;
	static std::vector<std::vector<std::pair<float, float>>> points;
	static GLdouble color[3];
public:
	// Draw all points as ploygon for the paritial ring
	static int draw();
	static void setPoints(const std::vector<std::vector<std::pair<float, float>>> &points) {		
		DrawRing::points.assign(points.begin(), points.end());
	}

	static void setColors(const std::vector<std::vector<float>> &colors) {
		DrawRing::colors.assign(colors.begin(), colors.end());
	}

	//// Tesselation draw
	static void myIdle(void)	{
		glutPostRedisplay();
	}
	static void CALLBACK PolyLine3DBegin(GLenum type)	{
		glBegin(type);
	}
	static void CALLBACK PolyLine3DVertex(GLdouble * vertex)
	{
		const GLdouble *pointer = (GLdouble *)vertex;
		  //glColor3d(1.0, 0, 0);  //在此设置颜色
		glColor3d(DrawRing::color[0], DrawRing::color[1], DrawRing::color[2]);
		//printf("color: %.2f, %.2f, %.2f\n", color[0], color[1], color[2]);
		glVertex3dv(pointer);
	}
	static void CALLBACK PolyLine3DEnd() {
		glEnd();
	}
	static GLUtesselator* tesser()	{
		GLUtesselator * tess;
		tess = gluNewTess();
		gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK*)())&PolyLine3DBegin);
		gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK*)())&PolyLine3DVertex);
		gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK*)())&PolyLine3DEnd);
		return tess;
	}	
	static void OnInit()	{	}	
	static void OnExit()	{	}
	static GLdouble pt[3];
	static void OnDraw()	{
		glClear(GL_STENCIL_BUFFER_BIT);

		GLdouble quad[22][3] =
		{
			{ 5, 5, 0 }, { 15, 5, 0 }, { 15, -5, 0 }, { 5, -5, 0 },
			{ 0, 5, 0 }, { -15, 10, 0 }, { -5, -10, 0 }, { -10, 5, 0 },
			{ -0.5, 1, 0 }, { -0.5, 2, 0 }, { 0.5, 2, 0 }, { 0.5, 1, 0 }

			, { 0.74, 0.25 }, { 0.76, 0.4 }, { 0.5, 0.75 }, { 0.1, 0.7 }, { 0.0, 0.54 }, { 0.5, 0.5 },
			{ 0, 0.5, 0 }, { -0.5, 0.1, 0 }, { -0.5, -0.1, 0 }, { -0.8, 0.5, 0 },
		};
		GLUtesselator* tess = NULL;

		tess = tesser();
		if (!tess) return;
		gluTessBeginPolygon(tess, NULL);
		gluTessBeginContour(tess);
		color[0] = 0, color[1] = 0.5, color[2] = 1;
		for (int i = 12; i < 18; i++)
		{
			gluTessVertex(tess, quad[i], quad[i]);
		}
		gluTessEndContour(tess);
		gluTessEndPolygon(tess);

		tess = tesser();
		if (!tess) return;
		gluTessBeginPolygon(tess, NULL);
		gluTessBeginContour(tess);
		color[0] = 1, color[1] = 0.5, color[2] = 0;
		for (int i = 18; i < 22; i++)
		{
			gluTessVertex(tess, quad[i], quad[i]);
		}
		gluTessEndContour(tess);
		gluTessEndPolygon(tess); 

		
		for (int i = 0; i < /*(int)DrawRing::points.size()*/1; i++) { // For each partial ring
			std::vector<std::pair<float, float>> ps = DrawRing::points[i];
			tess = tesser();
			if (!tess) return;			
			gluTessBeginPolygon(tess, NULL);
			gluTessBeginContour(tess);
			color[0] = colors[i][0], color[1] = colors[i][1], color[2] = colors[i][2];			
			for (int j = 0; j < (int)ps.size(); j++) {				
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
};
// static member should be defined here
std::vector<std::vector<float>> DrawRing::colors;
std::vector<std::vector<std::pair<float, float>>> DrawRing::points;
GLdouble DrawRing::color[3];
GLdouble DrawRing::pt[3];


int DrawRing::draw() {
	
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < (int)DrawRing::points.size(); i++) {
		glLoadIdentity();
		glClearColor(0, 0, 0, 0);
		glColor4f(DrawRing::colors[i][0], DrawRing::colors[i][1], DrawRing::colors[i][2], DrawRing::colors[i][3]);
		glFrontFace(GL_CW);
		glBegin(GL_TRIANGLE_STRIP);
		std::vector<std::pair<float, float>> ps = DrawRing::points[i];		
		for (int j = 0; j < (int)ps.size(); j++) {
			glVertex2f(ps[j].first, ps[j].second);
			//("%.2f, %.2f\n", ps[j].first, ps[j].second);
		}
		glEnd();
	}
	
	glFlush();
	return 0;
}

#endif


