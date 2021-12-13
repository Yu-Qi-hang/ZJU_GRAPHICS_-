// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// ʵ�鱨�������д����룬���Ժ�������⣬�Լ����õ�˳�򣬲���ȡ�˼��Ϊʲô�������ӵ��õģ�Ϊʲô���������������õģ��������ȵ������ֵ���о������⡣
#include <stdlib.h>
#include<cstdio>
#include "glut.h"


float fTranslate;
float fRotate    = 0.0f;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

//todo
//hint: some additional parameters may needed here when you operate the teapot
GLfloat teaxyz[3] = { 0,0,5 };
float tearotate = 0.0f;


void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glPushMatrix();
	glTranslatef(teaxyz[0], teaxyz[1], teaxyz[2]);
	glRotatef(90, 1, 0, 0);
	glRotatef(tearotate, 0, 1, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	//todo; hint: when operate the teapot, you may need to change some parameters
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;

	if (bPersp){
		gluPerspective(45.0f, 1, 5.0f, 40.0f);
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
	}
	else
		glOrtho(-3 ,3, -3, 3,-100,100);

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
//todo; hint: you may need another ARRAY when you operate the teapot

GLfloat light_pos[] = { 5,5,5,1 };
void key(unsigned char k, int x, int y)
{
	if (k >= 65 && k <= 90)k += 32;
	switch(k)
	{
	case 27 :
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
		eye[0] += 0.05f;
		center[0] += 0.05f;
		break;
			  }
	case 'd': {//todo
		eye[0] -= 0.05f;
		center[0] -= 0.05f;
		break;
			  }
	case 'w': {//todo
		eye[1] -= 0.05f;
		center[1] -= 0.05f;
		break;
			  }
	case 's': {//todo
		eye[1] += 0.05f;
		center[1] += 0.05f;
		break;
			  }
	case 'z': {//todo
		eye[2] -= 0.1f;
		break;
			  }
	case 'c': {//todo
		eye[2] += 0.1f;
		break;
			  }

			  //�����ز���
	case 'l': {//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		if(teaxyz[0]<2.0f)
		teaxyz[0] += 0.05f;
		break;
			  }
	case 'j': {//todo
		if (teaxyz[0] >-2.0f)
		teaxyz[0] -= 0.05f;
		break;
			  }
	case 'i': {//todo
		if (teaxyz[1] < 2.0f)
			teaxyz[1] += 0.05f;
		break;
			  }
	case 'k': {//todo
		if (teaxyz[1] > -2.0f)
			teaxyz[1] -= 0.05f;
		break;
			  }
	case 'e': {//todo
		tearotate += 10;
		if(tearotate>360)
		tearotate -=360;
		break;
			  }
	}
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_pos[] = {5,5,5,1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate    += 0.5f;

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	printf("WASDZC:\t���������������ǰ���ƶ�\nP:\t�л�ͶӰ��ʽ\nO:\t�л���Ⱦ��ʽ\n�ո��:\t��������ͣ��ת\nIKJLE:\t���Ʋ��ǰ�������ƶ�����ת\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


