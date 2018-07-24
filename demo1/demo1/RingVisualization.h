//Amended by Josiah
#ifndef _DRAW_RING_H
#define _DRAW_RING_H

#include <vector>
#include <utility>
#include <algorithm>
#include <gl/glut.h>
using namespace std;
class RingVisualization {

private:
	vector<array<float, 4>>* _colors;
	vector<pair<float, float>>* _points;
	void setPoints(vector<pair<float, float>>* points);
	void setColors(vector<array<float, 4>>* colors);
	GLdouble _color[3];
	static void CALLBACK PolyLine3DBegin(GLenum type);
	static void CALLBACK PolyLine3DVertex(GLdouble * vertex);
	static void CALLBACK PolyLine3DEnd();
public:
	RingVisualization(vector<pair<float, float>>* points, vector<array<float, 4>>* colors);
	vector<pair<float, float>> getPoints();
	vector<array<float, 4>> getColors();
	GLdouble* getColor();
	int draw();
	void myIdle(void);

	GLUtesselator* tesser()	{
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
			std::vector<std::pair<float, float>> ps = RingVisualization::points[i];
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
std::vector<std::vector<float>> RingVisualization::colors;
std::vector<std::vector<std::pair<float, float>>> RingVisualization::points;
GLdouble RingVisualization::color[3];
GLdouble RingVisualization::pt[3];




#endif


