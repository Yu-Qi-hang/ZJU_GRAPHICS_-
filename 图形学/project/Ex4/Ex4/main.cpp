#include <stdlib.h>
#include "glut.h"
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float eye[] = { 0, 4, 6 };
float center[] = { 0, 0, 0 };
float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false;
bool bDrawList = false;
GLint tableList = 0;
GLint rabbitList = 0;//兔子列表
int NumberOfRabbit = 1;

void DrawTable()
{
	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	glScalef(5, 1, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, -1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.5, -1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

GLint GenTableList()
{
	GLint lid = glGenLists(2);//2个空显示列表
	glNewList(lid, GL_COMPILE);//创建显示列表
	DrawTable();
	glEndList();

	glNewList(lid + 1, GL_COMPILE);//兔子显示列表
	DrawBunny();
	glEndList();
	return lid;
}

void DrawScene_List()
{
	glPushMatrix();
	glTranslatef(2.2, 4.5, 1.5);
	glScalef(2, 2, 2);
	//画兔子
	for (int i = 1; i <= NumberOfRabbit && i <= 16; i++) {
		glCallList(rabbitList);
		if (i % 4 == 0) //换行
			glTranslatef(-0.7f, 0.0f, 1.5f);
		else
			glTranslatef(0.0f, 0.0f, -0.5f);
	}
	glPopMatrix();
	glCallList(tableList);
}

void DrawScene()
{
	glPushMatrix();
	glTranslatef(2.2, 4.5, 1.5);
	glScalef(2, 2, 2);
	//画兔子
	for (int i = 1; i <= NumberOfRabbit; i++) {
		DrawBunny();
		if (i % 4 == 0) //换行
			glTranslatef(-0.7f, 0.0f, 1.5f);
		else
			glTranslatef(0.0f, 0.0f, -0.5f);
	}
	glPopMatrix();
	DrawTable();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	glViewport(0, 0, width, height);//设置视口
	glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作
	glLoadIdentity();//重置为单位矩阵

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);	//透视模式下，物体近大远小，参数分别为（视角，宽高比，近处，远处）

	glMatrixMode(GL_MODELVIEW);//对模型视景矩阵堆栈应用随后的矩阵操作
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27://ESC
	case 'q': {exit(0); break; }//退出
	case 'a': //左移
	{
		eye[0] += fDistance;
		center[0] += fDistance;
		break;
	}
	case 'd': //右移
	{
		eye[0] -= fDistance;
		center[0] -= fDistance;
		break;
	}
	case 'w': //上移
	{
		eye[1] -= fDistance;
		center[1] -= fDistance;
		break;
	}
	case 's': //下移
	{
		eye[1] += fDistance;
		center[1] += fDistance;
		break;
	}
	case 'z':
	{
		eye[2] *= 0.95;
		break;
	}
	case 'c':
	{
		eye[2] *= 1.05;
		break;
	}
	case 'l':
	{
		bDrawList = !bDrawList;	// 切换显示列表和非显示列表绘制方式
		break;
	}
	case ' ':
	{
		bAnim = !bAnim;
		break;
	}
	case 'i'://兔子数量增加
	{
		if(NumberOfRabbit<16)
			NumberOfRabbit++;
		break;
	}
	case 'k'://兔子数量减少
	{
		if (NumberOfRabbit > 1)
			NumberOfRabbit --;
		break;
	}
	default: break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0, 480, 0, 480, -1, 1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10, 10);//设置字符的起始位置
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清楚颜色缓存以及深度缓存
	glClearColor(0, 0.5, 0, 1);
	glLoadIdentity();//重置为单位矩阵
	//gluLookAt定义一个视图矩阵，并与当前矩阵相乘
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0, 5, 50)，Y轴向上
								//三个数组代表的分别是：相机在世界坐标中的位置
								//					相机对准的物体在世界坐标中的位置
								//					相机朝上的方向在世界坐标中的位置
	glEnable(GL_DEPTH_TEST);//启用深度测试，根据坐标远近自动隐藏被遮住的物体
	glEnable(GL_LIGHTING);//启用灯光
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = { 10, 10, 10, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);//设置环境光颜色
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);//设置0号光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);//设置0号光源的颜色
	glEnable(GL_LIGHT0);//开启0号光源

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glScalef(0.4, 0.4, 0.4);
	if (!bDrawList)
		DrawScene();						// old way
	else
		DrawScene_List();                  // new way

	getFPS();
	glutSwapBuffers();//交换缓冲区
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//对glut函数库进行初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//指定glutCreateWindow函数将要创建的窗口显示模式 RGB 深度缓存 双缓存模式
	glutInitWindowSize(480, 480);//设置窗口大小
	int windowHandle = glutCreateWindow("List");//打开设置好的窗口，进入glutMainLoop之前这个窗口不会显示

	glutDisplayFunc(redraw);//指定当前窗口需要重新绘制时调用的函数
	glutReshapeFunc(reshape);//当注册窗口大小改变时回调函数
	glutKeyboardFunc(key);//为当前窗口指定键盘回调
	glutIdleFunc(idle);//可以执行连续动画


	tableList = GenTableList();
	rabbitList = tableList + 1;
	glutMainLoop();
	return 0;
}