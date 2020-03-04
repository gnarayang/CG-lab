#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glx.h>

static int menu_id;
static int submenu_id;
static int value = 0;

void initGL()
{
    glClearColor(0, 0, 0, 0);
}

// void glutSolidTeapot(GLdouble size);
// void glutWireTeapot(GLdouble size);

void menu(int num){
	if(num == 0)
	{
		// glutDestroyWindow(window);
		exit(0);
  	}
  	else
  	{
		value = num;
	}
  	glutPostRedisplay();
} 

void createMenu()
{
	submenu_id = glutCreateMenu(menu);
    // glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Wired Teapot", 2);
    glutAddMenuEntry("Solid Teapot", 3);
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluOrtho2D(-1000, 1000, -1000, 1000);

	if(value == 1)
	{
		return; 
		glutPostRedisplay();
	}

	if(value == 3)
	{
		printf("Value = 2\n");
		glutSolidTeapot(0.5);
	}
	if(value == 2)
	{
		printf("Value = 3\n");
		glutWireTeapot(0.5);
	}

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Teapot");
	createMenu();
	glutDisplayFunc(display);
	initGL();
	glutMainLoop();
	return 0;
}