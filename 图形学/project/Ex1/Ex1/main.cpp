#include "gl/glut.h"
//#include"glut.h"

void drawtriangles(GLfloat a[3], GLfloat b[3], GLfloat c[3]);
void drawstar(GLfloat center[3], GLfloat rate, GLfloat angle);
void drawsquare(GLfloat a[3], GLfloat b[3], GLfloat c[3], GLfloat d[3]);
void display();
void ReSize(GLsizei w, GLsizei h);

int main (int argc,  char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(900, 600);
	glutCreateWindow("五星红旗"); 
	glutReshapeFunc(ReSize);
	glutDisplayFunc(display); 
	glutMainLoop(); 

	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.955, 0, 0.008);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 0.667, 1.0);
	glVertex3f(1.0, 0.667, 1.0);
	glVertex3f(1.0, -0.667, 1.0);
	glVertex3f(-1.0, -0.667, 1.0);
	glEnd();

	GLfloat angle[4] = { 51.33,71.5,99.5,120 };
	GLfloat GCenter[3] = { -0.667, 0.333, 0.0 };
	GLfloat GCenter1[3] = { -0.333, 0.067, 0.0 };
	//GLfloat GCenter2[3] = { 0.2, 0.2, 0.0 };
	GLfloat GCenter2[3] = { -0.2, 0.2, 0.0 };
	GLfloat GCenter3[3] = { -0.2, 0.4, 0.0 };
	GLfloat GCenter4[3] = { -0.333, 0.533, 0.0 };

	GLfloat rate = 1.0;
	drawstar(GCenter, rate, 0);
	rate = 0.333;
	drawstar(GCenter1, rate, angle[0]);
	drawstar(GCenter2, rate, angle[1]);
	drawstar(GCenter3, rate, angle[2]);
	drawstar(GCenter4, rate, angle[3]);

	glLoadIdentity();
	/*
	//画参考线
	glColor3f(0, 0, 0);
	for (GLfloat k = -0.995; k < 1; k = k + 0.06667) {
		GLfloat a[3] = { (GLfloat)k - 0.01,1,1 };
		GLfloat b[3] = { (GLfloat)k ,1,1 };
		GLfloat c[3] = { (GLfloat)k - 0.01,-1,1 };
		GLfloat d[3] = { (GLfloat)k ,-1,1 };
		drawsquare(a, b, c, d);
	}
	for (GLfloat k = -0.995; k < 1; k = k + 0.06667) {
		GLfloat a[3] = { 1,(GLfloat)k - 0.01,1 };
		GLfloat b[3] = { 1, (GLfloat)k ,1 };
		GLfloat c[3] = { -1,(GLfloat)k - 0.01,1 };
		GLfloat d[3] = { -1, (GLfloat)k ,1 };
		drawsquare(a, b, c, d);
	}
	glColor3f(1, 1, 1);
	GLfloat a[3] = { -0.01,1,1 };
	GLfloat b[3] = { 0 ,1,1 };
	GLfloat c[3] = { -0.01,-1,1 };
	GLfloat d[3] = { 0,-1,1 };
	drawsquare(a, b, c, d);
	GLfloat e[3] = { 1,-0.01,1 };
	GLfloat f[3] = { 1, 0 ,1 };
	GLfloat g[3] = { -1, -0.01,1 };
	GLfloat h[3] = { -1, 0 ,1 };
	drawsquare(e, f, g, h);
	//画参考线
	*/
	glutSwapBuffers();
}
void drawsquare(GLfloat a[3], GLfloat b[3], GLfloat c[3], GLfloat d[3]) {
	glLoadIdentity();
	glBegin(GL_QUADS);
	glVertex3f(a[0], a[1], a[2]);
	glVertex3f(b[0], b[1], b[2]);
	glVertex3f(c[0], c[1], c[2]);
	glVertex3f(d[0], d[1], d[2]);
	glEnd();
}
void drawtriangles(GLfloat a[3], GLfloat b[3], GLfloat c[3])
{
	glColor3f(0.98, 0.957, 0.031);
	glBegin(GL_TRIANGLES);
	glVertex3f(a[0], a[1], a[2]);
	glVertex3f(b[0], b[1], b[2]);
	glVertex3f(c[0], c[1], c[2]);
	glEnd();
}
void drawstar(GLfloat center[3], GLfloat rate, GLfloat angle)
{
	glLoadIdentity();
	GLfloat v[3][3] = { 0.2, 0.067,1.0,  -0.2, 0.067,1.0 ,  0.0, -0.067, 1.0 };
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glScalef(rate, rate, 1);
	drawtriangles(v[0], v[1], v[2]);
	glLoadIdentity();
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle + 72, 0.0, 0.0, 1.0);
	glScalef(rate, rate, 1);
	drawtriangles(v[0], v[1], v[2]);
	glLoadIdentity();
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle - 72, 0.0, 0.0, 1.0);
	glScalef(rate, rate, 1);
	drawtriangles(v[0], v[1], v[2]);
}
void ReSize(GLsizei w, GLsizei h)
{
	GLfloat Ratio;
	// 防止被0所除
	if (0 == h) {
		h = 1;
	}
	// 设置视口为窗口的大小
	glViewport(0, 0, w, h);
	// 选择投影矩阵，并重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 计算窗口的纵横比（像素比）
	Ratio = (GLfloat)w / (GLfloat)h;
	// 定义裁剪区域（根据窗口的纵横比，并使用正投影）
	GLfloat rt = 1.0;
	if (w <= h) {// 宽 < 高
		glOrtho(-rt, rt, -rt / Ratio, rt/ Ratio, 1.0, -1.0);
	}
	else {// 宽 > 高
		glOrtho(-rt * Ratio, rt * Ratio, -rt, rt, 1.0, -1.0);
	}
	// 选择模型视图矩阵，并重置坐标系统
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}