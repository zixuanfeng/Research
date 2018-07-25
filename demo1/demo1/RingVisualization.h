//Amended by Josiah
#ifndef _DRAW_RING_H
#define _DRAW_RING_H

#include <vector>
#include <utility>
#include <algorithm>
#include <E:\opengl\include\GL\glut.h>
using namespace std;
typedef GLvoid(*TessFuncPtr)();
class RingVisualization {

private:
	vector<array<float, 4>>* _colors;
	vector<pair<float, float>>* _points;
	void setPoints(vector<pair<float, float>>* points);
	void setColors(vector<array<float, 4>>* colors);
	GLdouble *_color;
	static void CALLBACK PolyLine3DBegin(GLenum type);
	static void CALLBACK PolyLine3DVertex(GLdouble * vertex, RingVisualization* t);
	static void CALLBACK PolyLine3DEnd(RingVisualization* t);
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
		
		gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK*)())(&PolyLine3DBegin));
		gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK*)())&PolyLine3DVertex);
		gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK*)())&PolyLine3DEnd);
		return tess;
	}	
	static void OnInit()	{	}	
	static void OnExit()	{	}
	GLdouble pt[3];
	void OnDraw();
};
#endif


