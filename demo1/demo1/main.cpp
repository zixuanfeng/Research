
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////Inialization Program///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include<stdio.h>
//#include<string.h>
//#include<iostream>
//
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//
////Window Dimensions
//const GLint WIDTH = 800, HEIGHT = 600;
//
//GLuint VAO, VBO, shader;
//
//
////vertex shader
//
//static const char* vShader="                               \n\
//	#version 330											\n\
//															\n\
//	layout(location = 0) in vec3 pos;						\n\
//															\n\
//	void main()												\n\
//{															\n\
//	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);  \n\
//}";
//
//
////fragment shader
//
//static const char* fShader = "								\n\
//	#version 330											\n\
//															\n\
//	out vec4 colour;										\n\
//															\n\
//	void main()												\n\
//{															\n\
//	colour = vec4(1.0,0.0,0.0,1.0);							\n\
//}";
//
//
////VAO 顶点数组对象 VBO 顶点缓冲对象 vbo是将顶点时数据从哭护短传输到GPU， vao是在几组顶点数组中间切换
//void CreateTriangle() {
//
//	GLfloat vertices[] = {
//		-1.0f, -1.0f, 0.0f,
//		1.0,-1.0,0.0f,
//		0.0f,1.0f,0.0f
//	};
//
//	//申请顶点数组对象，返回n个顶点数组对象的id
//	glGenVertexArrays(1, &VAO);
//	//绑定顶点数组，对象
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//
//
//}
//
//void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
//{
//	GLuint theShader = glCreateShader(shaderType);
//	const GLchar* theCode[1];
//	theCode[0] = shaderCode;
//
//	GLint codeLength[1];
//	codeLength[0] = strlen(shaderCode);
//
//	glShaderSource(theShader, 1, theCode, codeLength);
//	glCompileShader(theShader);
//
//	GLint result = 0;
//	GLchar eLog[1024] = { 0 };
//
//	
//	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
//		printf("Error Linking");
//		return;
//	}
//	glAttachShader(theProgram, theShader);
//	
//}
//
//
//
//
//void CompileShaders(){
//	shader = glCreateProgram();
//	if (!shader) {
//		printf("Error Createing shader Program!\n");
//		return;
//	}
//	AddShader(shader, vShader, GL_VERTEX_SHADER);
//	AddShader(shader, fShader, GL_FRAGMENT_SHADER);
//
//	GLint result = 0;
//	GLchar eLog[1024] = { 0 }; 
//
//	glLinkProgram(shader);
//	glGetProgramiv(shader, GL_LINK_STATUS, &result);
//	if (!result)
//	{
//		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);  
//		printf("Error Linking");
//			return;
//	}
//
//
//	glValidateProgram(shader);
//	glGetProgramiv(shader, GL_VALIDATE_STATUS,&result);
//	if (!result)
//	{
//		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
//		printf("Error Linking");
//		return;
//	}
//
//	}
//
//int main()
//{
//	//initialise GLFW
//	if (!glfwInit())
//	{
//		printf("GLFW initialled Failed!");
//		glfwTerminate();
//		return 1;
//	}
//
//
//	//setup GLFW window Properties
//	//openGLversion
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//	//core profile = no backwards compatibility
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT,"Test Window", NULL, NULL);
//	if (!mainWindow)
//
//	{
//		printf("GLFW window Creation failed!");
//		glfwTerminate();
//		return 1;
//	}
//
//
//	//Get Buffer size information
//	int bufferWidth, bufferHeight;
//	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
//
//	//set context for GLEW to use
//	glfwMakeContextCurrent(mainWindow);
//
//	//Allow modern extension features
//	glewExperimental = GL_TRUE;
//
//
//	if (glewInit()!= GLEW_OK)
//	{
//		printf("GLEW initialisation failed");
//		glfwDestroyWindow(mainWindow);
//		glfwTerminate();
//		
//		return 1;
//	}
//
//	//setup viewport size
//
//	glViewport(0, 0, bufferWidth, bufferHeight);
//
//	CreateTriangle();
//	CompileShaders();
//
//
//	//loop until window closed
//
//	while (!glfwWindowShouldClose(mainWindow))
//	{
//		//get and ahndle user input events
//
//		glfwPollEvents();
//		
//		//Clear Window
//		glClearColor(1.0f, 1.0f, 1.0f,1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//
//		glUseProgram(shader);
//
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(0);
//
//		glUseProgram(0);
//		glfwSwapBuffers(mainWindow);
//
//	}
//	
//
//	return 0;
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////Bar Chart/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <Windows.h>
//#include<iostream>
//#include <GL\freeglut.h>
//#include<GL\gl.h>
//#include<GL\GLU.h>
//#pragma comment(lib,"freeglut.lib")
//#define MAX_CHAR 128
//
//GLuint TextFont;
//
////初始化窗口大小
//GLsizei winWidth = 600, winHeight = 600;
//GLint xRaster = 30, yRaster = 5;
//GLubyte label[48] = { 'W','h','i','t','e',' ',' ', ' ',    'A','f','r','i','c','a','n',' ',    'I','n','d','i','a','n',' ',' ',
//'H','a','w','a','i','a','n',' ', ' ','A','s','i','a',' ',' ',' ',   'O','t','h','e','r',' ',' ',' ' };
//GLint dataValue[6] = {133,29,0,1,7,1};
//
//
//
//void XPrintString(const char *s)
//{
//	glPushAttrib(GL_LIST_BIT);
//
//	//调用每个字符对应的显示列表，绘制每个字符
//	for (; *s != '\0'; ++s)
//		glCallList(TextFont + *s);
//
//	glPopAttrib();
//}
//
//
//void init(void)
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	//做小窗口大小
//
//	glLoadIdentity();
//
//	TextFont = glGenLists(MAX_CHAR);
//
//	//把每个字符的绘制命令都装到对应的显示列表中
//	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, TextFont);
//	gluOrtho2D(100.0, 100.0, 100.0, 100.0);
//
//}
//
//void lineGraph(void)
//{
//	GLint month, k;
//	//line chart position
//	GLint x = 30;
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.0, 0.0, 1.0);
//	
////bar chart
//	for (k = 0; k<6; k++)
//	{
//		glRecti(20 + k * 70, 0, 40 + k * 70, dataValue[k]);
//	}
//
////line chart
//	glColor3f(0.0, 0.0, 1.0);
//	glBegin(GL_LINE_STRIP);
//	for (k = 0; k<6; k++)
//	{
//		glVertex2i(x + k * 70, dataValue[k]);
//	}
//	glEnd();
//
//
//
//	//glColor3f(0.0, 1.0, 0.0);
//	//for (k = 0; k<6; k++)
//	//{
//	//	glRasterPos2i(xRaster + k * 50, dataValue[k] - 4);
//	//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
//	//}
//
//	glColor3f(0.0, 0.0, 0.0);
//	xRaster = 10;   
//	for (month = 0; month<6; month++)
//	{
//		glRasterPos2i(xRaster, yRaster);
//		for (k = 8 * month; k<8 * month + 8; k++)
//		{
//			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
//		}
//		xRaster += 70, yRaster=-30;
//	}
//
//	//打印标题
//	glColor3f(0.0, 0.0, 0.0);
//	glRasterPos3f(10, 180, 0.0);
//	XPrintString("Brace Cancer Race Data");
//
//
//	glFlush();
//}
//void winReshapeFcn(int newWidth, int newHeight)
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glTranslatef(0.3, 1.0, 0.0);
//	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//
//}
//int main(int  argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(winWidth, winHeight);
//	glutCreateWindow("Line Chart Data Plot");
//
//	init();
//	glutDisplayFunc(lineGraph);
//	glutReshapeFunc(winReshapeFcn);
//
//	glutMainLoop();
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////Doughnut Chart///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <Windows.h>
//#include<iostream>
//#include <GL\freeglut.h>
//#include<GL\gl.h>
//#include<GL\GLU.h>
//#pragma comment(lib,"freeglut.lib")
//
//#include "loadcsv.h"
//#include "drawRing.h"
//#include "generatePolygonPoints.h"
//#include <random>
//#include <gl/glut.H>
//
//const int np = 1000;
//float PI = 3.1415926f;
//
//void generateAllRingPoints(std::string filename, std::vector<std::vector<std::pair<float, float>>> &grpps) {
//	LoadCSV lc(filename);
//	lc.parseData();
//
//	LoadCSV::lblfreq label_freqs;
//	std::vector<std::vector<std::pair<float, float>>> points;
//	int nrings = lc.getNumGroups();
//	float dr = 0.55f / nrings;
//	srand(1234);
//
//	float r1, r2 = 0.4f, start_angle = 0, end_angle = 0;
//	for (int i = 0; i < nrings; i++) {  // For each group (ring)
//		r1 = r2;
//		r2 = r1 + dr;
//		end_angle = rand() % 10 / 10.;
//		lc.getInnerGroupLabelFreqs(i, label_freqs);
//
//		float allsum = 0.f;
//		for (int ii = 0; ii < (int)label_freqs.size(); ii++) {
//			allsum += label_freqs[ii].second;
//		}
//		//float cursum = 0.f;		
//		for (int j = 0; j < (int)label_freqs.size(); j++) {  // For each partial ring 
//															 //cursum += label_freqs[j].second;
//			start_angle = end_angle;
//			end_angle = start_angle + label_freqs[j].second / allsum * 2 * PI;
//			GeneratePartRingPoints rp(np, r1, r2, start_angle, end_angle);
//			std::vector<std::pair<float, float>> points;
//			rp.generatePartRingPoints();
//			rp.getPoints(points);
//			grpps.push_back(points);
//		}
//	}
//}  
//
//
//void drawCircle() {
//	const float R1 = 0.8f, R2 = 0.6f, R3 = 0.4f;
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//
//	glLoadIdentity();
//	glClearColor(0, 0, 0, 0);
//	glColor4f(0, 0.6f, 0, 0);
//	glBegin(GL_QUAD_STRIP);
//
//	glVertex2f(0.1, 0.1);
//	glVertex2f(0.1, 0.2);
//	glVertex2f(0.2, 0.3);
//	glVertex2f(0.2, 0.4);
//	glVertex2f(0.3, 0.1);
//	glVertex2f(0.3, 0.2);
//
//
//	glEnd();
//
//
//
//	glFlush();
//}
//
//
//
//void draw() {
//	std::vector<std::vector<std::pair<float, float>>> grpps;
//	generateAllRingPoints("test.csv", grpps);
//	DrawRing::setPoints(grpps);
//	// set colors for each partial ring
//	std::srand(123);
//	std::vector<std::vector<float>> clrs;
//	for (int i = 0; i < (int)grpps.size(); i++) {
//		std::vector<float> clr;
//		for (int j = 0; j < 3; j++) {
//			clr.push_back(rand() % 100 / 100.f);
//		}
//		clr.push_back(0.f);
//		clrs.push_back(clr);
//	}
//	DrawRing::setColors(clrs);
//	
//	DrawRing::draw();
//}
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GLdouble quad[22][3] =
//{
//	{ 5, 5, 0 },{ 15, 5, 0 },{ 15, -5, 0 },{ 5, -5, 0 },
//{ 0, 5, 0 },{ -15, 10, 0 },{ -5, -10, 0 },{ -10, 5, 0 },
//{ -0.5, 1, 0 },{ -0.5, 2, 0 },{ 0.5, 2, 0 },{ 0.5, 1, 0 }
//
//,{ 0.74,0.25 },{ 0.76,0.4 },{ 0.5,0.75 },{ 0.1,0.7 },{ 0.0,0.54 },{ 0.5,0.5 },
//{ 0, 0.5, 0 },{ -0.5, 0.1, 0 },{ -0.5, -0.1, 0 },{ -0.8, 0.5, 0 },
//};
//void myIdle(void)
//{
//	glutPostRedisplay();
//}
////------------------------------------------------------------	OnDraw()
////
//GLdouble clr[3];
//
//void CALLBACK PolyLine3DBegin(GLenum type)
//{
//	glBegin(type);
//}
//void CALLBACK PolyLine3DVertex(GLdouble * vertex)
//{
//	const GLdouble *pointer = (GLdouble *)vertex;
//	
//	glColor3d(clr[0], clr[1], clr[2]);
//	glVertex3dv(pointer);
//}
//void CALLBACK PolyLine3DEnd()
//{
//	glEnd();
//}
//GLUtesselator* tesser()
//{
//	GLUtesselator * tess;
//	tess = gluNewTess();
//	gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK*)())&PolyLine3DBegin);
//	gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK*)())&PolyLine3DVertex);
//	gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK*)())&PolyLine3DEnd);
//	return tess;
//}
///////////////////////////////////////////////////////////////////////////////////
//void OnDraw()
//{
//	glClear(GL_STENCIL_BUFFER_BIT);
//
//	GLUtesselator* tess = tesser();
//	if (!tess) return;
//	gluTessBeginPolygon(tess, NULL);
//	gluTessBeginContour(tess);
//	clr[0] = 0, clr[1] = 0.5, clr[2] = 1;
//	for (int i = 12; i < 18; i++)
//	{
//		gluTessVertex(tess, quad[i], quad[i]);
//	}
//	gluTessEndContour(tess);
//	gluTessEndPolygon(tess);
//
//
//	tess = tesser();
//	if (!tess) return;
//	gluTessBeginPolygon(tess, NULL);
//	gluTessBeginContour(tess);
//	clr[0] = 1, clr[1] = 0.5, clr[2] = 0;
//	for (int i = 18; i < 22; i++)
//	{
//		gluTessVertex(tess, quad[i], quad[i]);
//	}
//	gluTessEndContour(tess);
//	gluTessEndPolygon(tess);
//
//	glutSwapBuffers();
//}
//
//
//
//int main(int argc, char **argv) {
//
//	printf("%s", "doughnout chart\n");
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(800, 800);
//	glutCreateWindow("Guage Chart");
//	glutDisplayFunc(&draw);
//	glutMainLoop();
//
//	return 0;
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////CUBE///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

////#include <Windows.h>
////#include<iostream>
////#include <fstream>
////#include <vector>
////#include <sstream>
//////#include <gl/glut.h>
////#include <GL\freeglut.h>
////#include<GL\gl.h>
////#include<GL\GLU.h>
//
////Cube has eight vertex, so we store 8 of them in a arry [] vertex, every vertex has 3 parameters
//static const float vertex_list[][3] =
//{
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	-0.5f, 0.5f, -0.5f,
//	0.5f, 0.5f, -0.5f,
//	-0.5f, -0.5f, 0.5f,
//	0.5f, -0.5f, 0.5f,
//	-0.5f, 0.5f, 0.5f,
//	0.5f, 0.5f, 0.5f,
//};
//
//
//
//// using an array to store the vertex []arraies and each array has 2 parameters将要使用的顶点的序号保存到一个数组里面 
////cube has 8 vertex, 12 lines, every line would be connected with two vertex
//static const GLint index_list[][2] =
//{
//{ 0, 1 },
//{ 2, 3 },
//{ 4, 5 },
//{ 6, 7 },
//{ 0, 2 },
//{ 1, 3 },
//{ 4, 6 },
//{ 5, 7 },
//{ 0, 4 },
//{ 1, 5 },
//{ 7, 3 },
//{ 2, 6 }
//};
//
//// begin draw the cube 绘制立方体
//
//void DrawCube(void)
//{
//	int i, j;
//
////everytime, glbegin need to use with glebd, and gline means draw lines, when we use glbegin(Here need to assign the shape)
//	glBegin(GL_LINES);
//	for (i = 0; i<12; ++i) // 12 条线段
//
//	{
//		for (j = 0; j<2; ++j) // 每条线段 2个顶点
//
//
//		{
//			//3fv means 3 parameters
//			glVertex3fv(vertex_list[index_list[i][j]]);
//		}
//	}
//	glEnd();
//}
//
//static float rotate = 0;
//static int times = 0;
//
//
////begin to render
//void renderScene(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glPushMatrix();
//
//	
//
//
//	times++;
//	if (times > 100)
//	{
//		times = 0;
//	}
//
//	if (times % 100 == 0)
//	{
//		rotate += 10;
//	}
//
//
//	//void glRotatef(GLfloat angle,  GLfloat x,  GLfloat y,  GLfloat z); 
//	glRotatef(rotate, 1, 1, 0);
//	/*glRotatef(rotate, 1, 0, 0);*/
//
//	glColor3f(1, 1, 1);
//
//	DrawCube();
//
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//void main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Rotating");
//	glutDisplayFunc(renderScene);
//	glutIdleFunc(renderScene);
//	glutMainLoop();
//}



///////////////////////////////////////////////////////////////////////////Bar Chart with CSV//////////////////////////////////////////////////////////////////////////////////////////
//#include <Windows.h>
//#include<iostream>
//#include <fstream>
//#include <vector>
//#include <sstream>
////#include <gl/glut.h>
//#include <GL\freeglut.h>
//#include<GL\gl.h>
//#include<GL\GLU.h>
//#pragma comment(lib,"freeglut.lib")
//#define MAX_CHAR 128
//
//GLuint TextFont;
//
////³õÊ¼»¯´°¿Ú´óÐ¡
//GLsizei winWidth = 600, winHeight = 600;
//GLint xRaster = 30, yRaster = 5;
//
//// One label occupies at maximum 8 bytes (letters).
//GLubyte label[108];
//
//GLint dataValue[108];
//
//
//// read datavalue and label by using the ifstream 
//int readFile() {
//	std::ifstream data("Book1.csv", std::ifstream::in);
//	if (data.fail()) {
//		char buf[500];
//		//checking errors or check the excel errors 
//		strerror_s(buf, errno);
//		printf("%s\n", buf);
//	}
//
//	std::string line;
//	std::getline(data, line);
//	std::stringstream sstr(line);
//	std::string lbl;
//
//	// Parse one row (a group of labels)	
//	//print the labels
//	int i = 0;
//	while (std::getline(sstr, lbl, ',')) {
//		for (int j = 0; j < lbl.length(); j++) label[i * 8 + j] = lbl[j];
//		i++;
//	}
//
//	// Parse next row (corresponding frequencies)
//	std::getline(data, line);
//	//input the string
//	std::stringstream sstr2(line);
//	std::string freq;
//	i = 0;
//	while (std::getline(sstr2, freq, ',')) {
//		std::stringstream sstr3;
//		sstr3 << freq;
//		float frq;
//		sstr3 >> frq;
//		dataValue[i++] = (int)frq;
//	}
//	data.close();
//
//	return i;
//}
//
//
//void XPrintString(const char *s)
//{
//	glPushAttrib(GL_LIST_BIT);
//
//
//	for (; *s != '\0'; ++s)
//
//		//print the list
//		glCallList(TextFont + *s);
//
//	glPopAttrib();
//}
//
//
//void init(void)
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0); // white back ground
//	glMatrixMode(GL_PROJECTION);
//	//×öÐ¡´°¿Ú´óÐ¡
//
//	glLoadIdentity();
//
//	TextFont = glGenLists(MAX_CHAR);
//
//	//print the table name 
//	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, TextFont);
//	gluOrtho2D(100.0, 100.0, 100.0, 100.0);
//}
//
//void lineGraph(void)
//{
//	GLint Race, k;
//	//line chart position
//	GLint x = 30;
//	glClear(GL_COLOR_BUFFER_BIT);
//
//
//
//	glColor3f(0.0, 0.0, 1.0);
//
//	//bar chart
//	for (k = 0; k<6; k++)
//	{
//		glRecti(20 + k * 70, 0, 40 + k * 70, dataValue[k]);
//	}
//
//	//line chart
//	glColor3f(0.0, 0.0, 1.0);
//	glBegin(GL_LINE_STRIP);
//	for (k = 0; k<6; k++)
//	{
//		glVertex2i(x + k * 70, dataValue[k]);
//	}
//	glEnd();
//
//
//	// output label
//	glColor3f(0.0, 0.0, 0.0);
//	xRaster = 10;
//	yRaster = -30;
//	for (Race = 0; Race<6; Race++)
//	{
//		glRasterPos2i(xRaster, yRaster);
//		for (k = 8 * Race; k<8 * Race + 8; k++)
//		{
//			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
//		}
//		xRaster += 70;
//	}
//
//	//print the table name
//	glColor3f(0.0, 0.0, 0.0);
//	glRasterPos3f(10, 180, 0.0);
//	XPrintString("Race");
//
//
//	glFlush();
//}
//void winReshapeFcn(int newWidth, int newHeight)
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glTranslatef(0.3, 1.0, 0.0);
//	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//int main(int  argc, char** argv)
//{
//	readFile();
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(winWidth, winHeight);
//	glutCreateWindow("Line Chart Data Plot");
//
//	init();
//	glutDisplayFunc(lineGraph);
//	glutReshapeFunc(winReshapeFcn);
//
//	glutMainLoop();
//}
//
//


/////////////////////////////////////////////////////////////////Ring////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <gl/glut.h>

#include <GL\freeglut.h>
#include<GL\gl.h>
#include<GL\GLU.h>
#pragma comment(lib,"freeglut.lib")

const int NUM_PT = 1000;
float M_PI = 3.1415926f;

void generate_points(std::string filename, std::vector<std::vector<std::pair<float, float>>> &grpps) {
	// 打开文件
	std::ifstream data(filename, std::ifstream::in);
	if (data.fail()) { // 文件打开失败
		char buf[500];
		strerror_s(buf, errno);
		printf("%s\n", buf);
	}
	// 读取label和data
	std::string line;
	std::vector<std::pair<std::string, std::vector<std::pair<std::string, float>>>> label_freqs;
	while (std::getline(data, line)) { // 按行读取
		std::stringstream sstr(line);
		std::string grplabel;
		// 读取组label
		getline(sstr, grplabel, ',');
		std::string label;

		// 一组label和data value
		std::vector<std::pair<std::string, float>> gp;
		// 读取label
		while (getline(sstr, label, ',')) {
			gp.push_back(std::pair<std::string, float>(label, 0.f));
		}

		// 读取data行
		getline(data, line);
		std::stringstream sstr2(line);
		std::string freq;
		getline(sstr2, freq, ',');
		int i = 0;
		while (getline(sstr2, freq, ',')) {
			std::stringstream sstr3;
			sstr3 << freq;
			float frq;
			sstr3 >> frq;
			gp[i++].second = frq;
			if (i == gp.size()) {
				break;
			}
		}
		if (i != gp.size()) { // label和数值个数不匹配
			std::printf("Error: Not enough frequency values.\n");
			return;
		}
		else {
			label_freqs.push_back(std::pair<std::string, std::vector<std::pair<std::string, float>>>(grplabel, gp));
		}
	}
	data.close();


	//std::vector<std::vector<std::pair<float, float>>> points;
	int nrings = label_freqs.size();
	// 每个环半径
	float dr = 0.55f / nrings;
	// 随机数（后面产生随机开始角度）
	srand(1234);
	// 环的内外圆半径，起止角度
	float r1, r2 = 0.4f, start_angle = 0, end_angle = 0;
	// 逐个组group绘制
	for (int i = 0; i < nrings; i++) {  // For each group (ring)
		r1 = r2;
		r2 = r1 + dr;
		end_angle = rand() % 10 / 10.;
		std::string grplabel = label_freqs[i].first;
		std::vector<std::pair<std::string, float>>& lf = label_freqs[i].second;
		// 当前group所有数字和
		float allsum = 0.f;
		for (int ii = 0; ii < (int)lf.size(); ii++) {
			allsum += lf[ii].second;
		}
		// 每个label对应的部分环
		for (int j = 0; j < (int)lf.size(); j++) {  // For each partial ring 
			start_angle = end_angle;
			end_angle = start_angle + lf[j].second / allsum * 2 * M_PI;

			// 产生ring对应的绘制点
			std::vector<std::pair<float, float>> points;
			// 内外环上各取一点
			float dangle = (end_angle - start_angle) / NUM_PT;
			float angle = end_angle;
			for (int i = 0; i < NUM_PT; i++) {
				angle -= dangle;
				points.push_back(std::pair<float, float>(r1*cos(angle), r1*sin(angle)));
				points.push_back(std::pair<float, float>(r2*cos(angle), r2*sin(angle)));
			}
			grpps.push_back(points);
		}
	}
}

void draw_r() {
	std::vector<std::vector<std::pair<float, float>>> grpps;
	generate_points("test.csv", grpps);


	std::srand(1235);
	// 绘制(每次一个半环）
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < (int)grpps.size(); i++) {
		glLoadIdentity();
		glClearColor(0, 0, 0, 0);
		// 随机产生颜色
		float clr[4] = { 0.f };
		for (int j = 0; j < 3; j++) {
			clr[j] = (rand() % 100 / 100.f);
		}
		glColor4f(clr[0], clr[1], clr[2], clr[3]);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_STRIP);
		std::vector<std::pair<float, float>> &ps = grpps[i];
		for (int j = 0; j < (int)ps.size(); j++) {
			glVertex2f(ps[j].first, ps[j].second);
		}
		glEnd();
	}

	glFlush();
}


int main(int argc, char **argv) {

	printf("%s", "hello hola\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Guage Chart");
	glutDisplayFunc(&draw_r);
	glutMainLoop();



	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////圆///////////////////////////////////////

//#include <gl/glut.h>
//#include <GL\freeglut.h>
//#include<GL\gl.h>
//#include<GL\GLU.h>
//#include "math.h"
//#include <iostream>
//
//using namespace std;
//
//
//int n = 3600;  //圆绘制次数
//float PI = 3.1415926f;
//float R = 0.8f;  //半径
//
//
//
////
////void myDisplay(void)
////{
////	//画圆
////	glClear(GL_COLOR_BUFFER_BIT);
////	glEnable(GL_BLEND);
////	glBlendFunc(GL_ONE, GL_ZERO);
////
////	glColor4f(0, 0, 1, 0);
////	glBegin(GL_POLYGON);
////	for (int i = 0; i<n; i++)
////	{
////		glVertex2f(R*cos(2 * PI*i / n), R*sin(2 * PI*i / n));   //定义顶点
////	}
////
////
////	glColor4f(1, 0, 0, 0.5);
////	glRectf(-1, -1, 0.5, 0.5);
////	glColor4f(0, 1, 0, 0.5);
////	glRectf(-0.5, -0.5, 1, 1);
////	glEnd();
////	glutSwapBuffers();
////}
//void setLight(void)
//{
//	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
//	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
//}
////每一个球体颜色不同。所以它们的材质也都不同。这里用一个函数来设置材质。
//void setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
//{
//	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
//	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
//}
////有了这两个函数，我们就可以根据前面的知识写出整个程序代码了。这里只给出了绘制的部分，其它部分大家可以自行完成。
//void myDisplay(void)
//{
//	// 定义一些材质颜色
//	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
//	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };
//
//	// 清除屏幕
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// 启动混合并设置混合因子
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	// 设置光源
//	setLight();
//
//	// 以(0, 0, 0.5)为中心，绘制一个半径为.3的不透明红色球体（离观察者最远）
//	setMatirial(red_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, 0.5f);
//	glutSolidSphere(0.3, 30, 30);
//	glPopMatrix();
//
//	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
//	glDepthMask(GL_FALSE);
//
//	// 以(0.2, 0, -0.5)为中心，绘制一个半径为.2的半透明蓝色球体（离观察者最近）
//	setMatirial(blue_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.2f, 0.0f, -0.5f);
//	glutSolidSphere(0.2, 30, 30);
//	glPopMatrix();
//
//	// 以(0.1, 0, 0)为中心，绘制一个半径为.15的半透明绿色球体（在前两个球体之间）
//	setMatirial(green_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.1, 0, 0);
//	glutSolidSphere(0.15, 30, 30);
//	glPopMatrix();
//
//	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
//	glDepthMask(GL_TRUE);
//
//	glutSwapBuffers();
//}
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);   //初始化GLUT
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(1000, 1000);
//	glutCreateWindow("My first OpenGL program");
//	/*glutReshapeFunc(reshape);*/
//	glutDisplayFunc(*&myDisplay);   //回调函数 
//	glutMainLoop();    //持续显示，当窗口改变会重新绘制图形
//	return 0;
//}