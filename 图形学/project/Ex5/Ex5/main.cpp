// glutEx1.cpp : 定义控制台应用程序的入口点。
//
#include <stdlib.h>
#include "glut.h"
#include<cstdio>

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;


//环境光
GLfloat light_x = 5.0;
GLfloat light_y = 5.0;
GLfloat light_z = 5.0;
int colorset = 1;
//聚光灯朝向和角度
GLfloat spotangle = 4.0;
GLfloat spot_x = 0.0;
GLfloat spot_y = 0.2;
GLfloat spot_z = -1.0;

void Draw_Leg();
void Set_Color(GLfloat color1, GLfloat color2, GLfloat color3);
void Draw_Table()
{
	GLfloat amb[] = { 0.24725f,0.1995f,0.0745f,1.0f };
	GLfloat diff[] = { 0.85f, 0.65f, 0.2f, 1.0f };
	GLfloat spec[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat shine = 50.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	Set_Color(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	Set_Color(0, 1, 0);
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	Set_Color(1, 1, 0);
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	Set_Color(0, 1, 1);
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	Set_Color(0, 0, 1);
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}
void Set_Color(GLfloat color1, GLfloat color2, GLfloat color3) {
	GLfloat color[] = { 0, 0, 0 ,1 };
	color[0] = color1;
	color[1] = color2;
	color[2] = color3;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
}
void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	} else {
		glOrtho(-3 ,3, -3, 3,-100,100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
	if (k >= 65 && k <= 90)
		k += 32;
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
			  }
	case 'd': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
			  }
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
			  }
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
			  }
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
			  }
	case 'c': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
			  }
	case 'j': {//左
		light_x += 0.2f;
		break;
			}
	case 'l': {//右
		light_x -= 0.2f;
		break;
			}
	case 'i': {//上
		light_y += 0.2f;
		break;
			}
	case 'k': {//下
		light_y -= 0.2f;
		break;
			}
	case 'n': {//前
		light_z += 0.2f;
		break;
			}
	case 'm': {//后
		light_z -= 0.2f;
		break;
			}
	case 'b': {
		colorset = !colorset;
		break;
		}
	case '4': {
		spot_x += 0.2f;
		break;
	}
	case '6': {
		spot_x -= 0.2f;
		break;
	}
	case '8': {
		spot_y += 0.2f;
		break;
	}
	case '5': {
		spot_y -= 0.2f;
		break;
	}
	case '1': {
		spot_z += 0.2f;
		break;
	}
	case '3': {
		spot_z -= 0.2f;
		break;
	}
	case '+': {
		if (spotangle < 10.0f)	spotangle += 0.2f;
		break;
	}
	case '-': {
		if (spotangle > 1.0f)	spotangle-= 0.2f;
		break;
	}
	}

	updateView(wHeight, wWidth);
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat RED[] = { 1.0,0.0,0.0,1.0 };//环境光颜色
	GLfloat light_pos[] = { light_x, light_y, light_z , 1 };//环境光位置

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	if (colorset)
		glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	else
		glLightfv(GL_LIGHT0, GL_AMBIENT, RED);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_LIGHT0);

	GLfloat spotsource[] = { 0, 0, 5.0, 1.0 };
	GLfloat lightDir[] = { spot_x, spot_y, spot_z,1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, white);             //设置环境光成分
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);                    //设置镜面光成分
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);                     //设置漫射光成分

	glLightfv(GL_LIGHT1, GL_POSITION, spotsource);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotangle);             //裁减角度
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);          //光源方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);                    //聚集度
	glEnable(GL_LIGHT1);

	glRotatef(fRotate, 0.0f, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Table();						// Draw triangle

	if (bAnim) fRotate    += 0.5f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	printf("不分大小写\nP\t切换投影模式\nO\t切换显示模式\nB\t切换环境光颜色\n空格\t控制整体旋转\nWSADZC\t控制摄像机位置\nIKJLNM\t控制光源位置\n854613\t控制聚光灯方向\n+-\t控制聚光灯覆盖角度\nQ/ESC\t退出\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


