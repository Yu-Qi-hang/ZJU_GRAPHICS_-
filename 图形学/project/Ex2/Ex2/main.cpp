// main.cpp : 定义控制台应用程序的入口点。
#include "glut.h"

float fTranslate=-1.0f;
float fRotate=0.0f;
float fScale=1.0f;

const GLfloat pointlist[][3] =
{
	-0.5f, -0.4f, 0.00f,
	0.5f, -0.4f, 0.00f,
	0.5f, 0.4f, 0.0f,
	-0.5f, 0.4f, 0.00f,
	-0.5f, 0.4f, 0.20f,
	0.5f, 0.4f, 0.20f,
	0.5f, -0.4f, 0.20f,
	-0.5f, -0.4f, 0.20f,
};
const GLint linepoint[][4] =
{ {0, 1, 2, 3}, {2, 3, 4, 5}, {4, 5, 6, 7}, {6, 7, 0, 1} };

void Draw_cubic() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int i = 0; i < 4; ++i){
		glBegin(GL_POLYGON);
			for (int j = 0; j < 4; ++j)
			{
				glVertex3fv(pointlist[linepoint[i][j]]);
			}
		glEnd();
	}
}
void Draw_Desks()
{
	Draw_cubic();
	glScalef(0.2f, 0.25f, 3.0f);
	glTranslatef(-1.5f, -1.0f, -0.2f);
	Draw_cubic();
	glTranslatef(0.0f, 2.0f, 0.0f);
	Draw_cubic();
	glTranslatef(3.0f, 0.0f, 0.0f);
	Draw_cubic();
	glTranslatef(0.0f, -2.0f, 0.0f);
	Draw_cubic();
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}


void redraw()
{
// If want display in wireframe mode
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glPushMatrix();
		glTranslatef(-2.3f, 0.0f,-6.0f);		// Place the triangle Left
		glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
		Draw_Desks();						// Draw triangle					
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
		glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
		Draw_Desks();						// Draw triangle
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.3f, 0.0f, -6.0f);			// Place the triangle at Center
		glScalef(fScale, fScale, fScale);
		Draw_Desks();						// Draw triangle
	glPopMatrix();

	fTranslate += 0.001f;
	fRotate    += 0.5f;
	fScale -= 0.001f;

	if(fTranslate > 1.0f) fTranslate = -1.0f;
	if (fScale < 0.5f) fScale = 1.0f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);                                                  
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);		
	glutIdleFunc(idle);					
	glutMainLoop();

	return 0;
}


