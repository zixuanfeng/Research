#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <windows.h>

//#include <gl/glut.h>

#include <GL\freeglut.h>
#include<GL\gl.h>
#include<GL\GLU.h>
#pragma comment(lib,"freeglut.lib")

GLuint Font;
const int NUM_PT = 5000;
const float M_PI = 3.1415926f;
const int GREY = 0xD9D9D9;

// Colors: 圆环可以使用的颜色表
//different colors for different rings
const int COLORS[][5] = { { 0xFFB6C1, 0xFF69B4, 0xFF1493, 0xDB7093, 0xC71585 },   // Pink
{ 0xD8BFD8, 0xDA70D6, 0xFF00FF, 0x9932CC, 0x663399 },   // Purple
{ 0xFFA07A, 0xF08080, 0xDC143C, 0xDD0000, 0xB22222 },   // Red
{ 0xFFA500, 0xFF7F50, 0xFF4500, 0xFFD700, 0xFFE4B5 },   // Orange-Yellow
{ 0x7FFF00, 0x32CD32, 0x90EE90, 0x3CB371, 0x008000 },   // Green
{ 0x20B2AA, 0x00FFEE, 0x7FFFD4, 0x40E0D0, 0x00CED1 },   // Cyan 
{ 0x4682B4, 0x87CEFA, 0x6495ED, 0x4169E1, 0x00008B },   // Blue
{ 0xFFEBCD, 0xDEB887, 0xBC8F8F, 0xB8860B, 0xA0522D }   // Brown
													   //{0xFFFAFA, 0xF0FFF0, 0xF0FFFF, 0xF8F8FF, 0xFFF5EE},   // Shallow-white 1
													   //{0xF5F5DC, 0xFFFAF0, 0xFAEBD7, 0xFFF0F5, 0xFFE4E1}    // Shallow-white 2
};

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::stringstream;
using std::ifstream;

/** A part of ring. 半环  half rings, everytime we start from the half rings
*/
typedef struct {
	string label;
	float start_angle;
	float end_angle;
	int color;
	float percent;
	float freq;
	vector<pair<float, float>> points;
}*pRing, Ring;
/** 一组（完整圆环）
entire rings
*/
typedef struct {
	string label;
	vector<Ring> rings;
}*pRingsGroup, RingsGroup;



/** 读取数据文件，解析label和data，以组的形式返回到数组groups，每组表示一个完整圆环（有多个半圆Ring组成）
reading the file, and analysis the label and data, and return the array back to group, every group represent a entire ring. 
*/
void generate_points(string filename, vector<RingsGroup> &groups) {
	// 打开文件
	ifstream data(filename, ifstream::in);
	if (data.fail()) { // 文件打开失败 Fail to load the file
		char buf[500];
		strerror_s(buf, errno);
		printf("%s\n", buf);
	}

	// 读取label和data 
	//read the lable and data
	string line;
	groups.clear();
	int ind = 0;
	while (std::getline(data, line)) { // 按行读取 read the data line by line
		stringstream sstr(line);
		string grplabel;

		// 读取组label read the label
		getline(sstr, grplabel, ',');
		RingsGroup rg;
		rg.label = grplabel;
		groups.push_back(rg);
		string label;
		// 一组label和data value /////one set of label and data velue
		// 读取label //read the label
		while (getline(sstr, label, ',')) {
			Ring r;
			r.label = label;
			groups[ind].rings.push_back(r);
		}

		// 读取data行 read the data line 
		getline(data, line);
		stringstream sstr2(line);
		string freq;
		// 跳过第一个空白数字  //skip the first empty number
		getline(sstr2, freq, ',');
		int i = 0;
		while (getline(sstr2, freq, ',')) {
			std::stringstream sstr3;
			sstr3 << freq;
			float frq;
			sstr3 >> frq;
			groups[ind].rings[i++].freq = frq;

			if (i == groups[ind].rings.size()) {
				break;
			}
		}
		if (i != groups[ind].rings.size()) { // label和数值个数不匹配    //label and the frequency values are not match
			std::printf("Error: Not enough frequency values.\n");
			return;
		}

		ind += 1;  // next group of partial rings
	}
	data.close();
	// number of rings (groups)
	int nrings = ind;
	// 每个环半径   every circle R 
	float dr = 0.65f / nrings * 2.f / 3.f;
	float dinterval = dr / 2;  // 环间隔为环宽的1/2  the distance between each circle is 1/2

							   // 随机数（后面产生随机开始角度、颜色）//random numbers and angles
	srand(85);
	// 环的内外圆半径，起止角度  the circle consist with two lines, it has two radius, one is outter and one is inner. 
	float r1, r2 = 0.3f, start_angle = 0, end_angle = 0;
	int color_ind = 0;
	// 逐个组group绘制 draw the ring group by group
	for (int i = 0; i < nrings; i++) {  // For each group
		r1 = r2 + dinterval;
		r2 = r1 + dr;
		end_angle = rand() % 10 / 10.;
		string grplabel = groups[i].label;
		vector<Ring> &rings = groups[i].rings;
		// 当前group所有数字和 total number of groups 
		float allsum = 0.f;
		for (int ii = 0; ii < (int)rings.size(); ii++) {
			// 频率可能为负数   frenquency could be negative 
			allsum += std::abs(groups[i].rings[ii].freq);
		}
		//计算角度、颜色、绘制点  calculate the angle, color and position
		for (int j = 0; j < (int)rings.size(); j++) {  // For each partial ring 
			start_angle = end_angle;
			float frq = rings[j].freq;
			end_angle = start_angle + std::abs(frq) / allsum * 2 * M_PI;
			int color = 0;
			if (frq < 0) {
				// 负值灰色   negative will be grey
				color = GREY;
			}
			else {
				// 选取颜色   //pick the color 
				color = COLORS[color_ind++ % 8][rand() % 5];
			}
			rings[j].start_angle = start_angle;
			rings[j].end_angle = end_angle;
			rings[j].color = color;
			rings[j].percent = std::abs(frq) / allsum;
			// 产生ring对应的绘制点, 内外环上各取一点    found the position in outter and inner rings
			float dangle = (end_angle - start_angle) / NUM_PT;
			float angle = end_angle;
			for (int i = 0; i < NUM_PT; i++) {
				angle -= dangle;
				rings[j].points.push_back(std::pair<float, float>(r1*cos(angle), r1*sin(angle)));
				rings[j].points.push_back(std::pair<float, float>(r2*cos(angle), r2*sin(angle)));
			}
		}
	}
}

/** 绘制字符   //begin to print the text
*/
void draw_font(const char *s)
{
	glPushAttrib(GL_LIST_BIT);
	// 调用每个字符对应的显示列表，绘制每个字符  //draw the text 
	for (; *s != '\0'; s++)
		glCallList(Font + *s);
	glPopAttrib();
}


void draw_r() {
	vector<RingsGroup> groups;
	generate_points("test.csv", groups);

	// 半环的个数   //how many half circles 
	int n_rings = 0;
	for (int i = 0; i < (int)groups.size(); i++) {
		for (int j = 0; j < (int)groups[i].rings.size(); j++) {
			if (groups[i].rings[j].color != GREY) {
				n_rings++;
			}
		}
	}

	// setup legend size for ring
	float rect_side = 0.5 / n_rings * 2.f / 3;
	float rect_interval = 0.5 / n_rings * 1.f / 3;
	int ind_ring = 0;
	float legend_xpos = -0.6f;
	float legend_ypos = 0.25f;

	// 绘制
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < (int)groups.size(); i++) {
		for (int j = 0; j < (int)groups[i].rings.size(); j++) {
			vector<pair<float, float>> &ps = groups[i].rings[j].points;
			int color = groups[i].rings[j].color;
			float percent = groups[i].rings[j].percent;
			glViewport(0, 0, 600, 600);  // 画图范围 (0,0) is lower left	
										 // 绘制(每次一个半环）
			glLoadIdentity();
			glColor4f(((color >> 16) & 0xFF) / 255.f, ((color >> 8) & 0xFF) / 255.f, (color & 0xFF) / 255.f, 0.f);
			glBegin(GL_TRIANGLE_STRIP);
			for (int jj = 0; jj < (int)ps.size(); jj++) {
				glVertex2f(ps[jj].first, ps[jj].second);
			}
			glEnd();

			// number label
			glColor3f(1.0, 1.0, 1.0);
			int midpt = ps.size() / 2;
			float midx = (ps[midpt].first + ps[midpt + 1].first) / 2.f;
			float midy = (ps[midpt].second + ps[midpt + 1].second) / 2.f;
			float dr = std::sqrt((ps[midpt].first - ps[midpt + 1].first)*(ps[midpt].first - ps[midpt + 1].first) + (ps[midpt].second - ps[midpt + 1].second)*(ps[midpt].second - ps[midpt + 1].second));

			// slightly move to left or right for some angle
			// 纠正位置误差   /adjust the mistakes 
			if (std::abs(midy / midx) < 3.0) midx -= 1.f / 3 * dr;
			glRasterPos2f(midx, midy);
			char buf[50];
			sprintf_s(buf, "%d", (int)(percent * 100));
			draw_font(buf);

			// draw legend on the right
			if (color != GREY) {
				glViewport(600, 0, 200, 600);
				glLoadIdentity();
				glColor4f(((color >> 16) & 0xFF) / 255.f, ((color >> 8) & 0xFF) / 255.f, (color & 0xFF) / 255.f, 0.f);
				glRectf(legend_xpos, legend_ypos, legend_xpos + rect_side * 2, legend_ypos - rect_side);

				// text
				glColor3f(1.0, 1.0, 1.0);
				glRasterPos2f(legend_xpos + rect_side * 2 + 0.04, legend_ypos - 4. / 5 * rect_side);
				sprintf_s(buf, "%s %s", groups[i].label.c_str(), groups[i].rings[j].label.c_str());
				draw_font(buf);
				//向下移动y
				legend_ypos -= (rect_side + rect_interval);
			}
		}
	}

	glFlush();
}

/** GL初始化
*/
void init_r(void) {
	glClearColor(0.0588, 0.1451, 0.2235, 0); // set back ground color (kind of navy blue)
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	Font = glGenLists(128);

	//把每个字符的绘制命令都装到对应的显示列表中   //print the text 
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, Font);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 设定x,y坐标范围为[-1，1]  //set up the x and y range from -1 to 1 

}

int main(int argc, char **argv) {

	printf("%s", "hello hola\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Guage Chart");
	init_r();
	glutDisplayFunc(&draw_r);
	glutMainLoop();

	//system("pause");
	return 0;
}
