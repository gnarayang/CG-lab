#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glx.h>

int n;

void initGL()
{
    glClearColor(0, 0, 0, 0);
}

void drawTriangles(float xleft, float yleft, float xup, float yup, float xright, float yright, int levels)
{
	if(levels == 1)
	{
		glVertex2f(xleft, yleft);
		printf("%f %f\n", xleft, yleft);
		glVertex2f(xup, yup);
		printf("%f %f\n", xup, yup);
		glVertex2f(xright, yright);
		printf("%f %f\n", xright, yright);
	}
	else
	{
		// Left
		drawTriangles(xleft, yleft, (xleft+xup)/2, (yleft+yup)/2, (xleft+xright)/2, (yleft+yright)/2, levels - 1);
		// Up
		drawTriangles((xleft+xup)/2, (yleft+yup)/2, xup, yup, (xright+xup)/2, (yright+yup)/2, levels-1);
		// Right
		drawTriangles((xleft+xright)/2, (yleft+yright)/2, (xup+xright)/2, (yup+yright)/2, xright, yright, levels-1);
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1000, 1000, -1000, 1000);

	glBegin(GL_TRIANGLES);

	drawTriangles(-500, 0, 0, 500*sqrt(3), 500, 0, n);

	glEnd();
	glFlush();	
}

int main(int argc, char **argv)
{
	printf("Enter the number of revursive levels\n");
	scanf("%d", &n);
	if(n < 1)
	{
		printf("The recursive levels should be greater than 0\n");
		return 0;
	}
	glutInit(&argc, argv);
	glutCreateWindow("Sierpinski triangle");
	glutDisplayFunc(display);
	initGL();
	glutMainLoop();
	return 0;
}