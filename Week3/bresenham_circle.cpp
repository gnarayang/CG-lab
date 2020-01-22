#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int x_1, x_2, y_1, y_2;
int dx, dy;
int step;
int xinc, yinc;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawCircle(int xc, int yc, int x, int y) 
{ 
  glBegin(GL_POINTS);

    glVertex2i(xc+x, yc+y); 
    glVertex2i(xc-x, yc+y); 
    glVertex2i(xc+x, yc-y); 
    glVertex2i(xc-x, yc-y); 
    glVertex2i(xc+y, yc+x); 
    glVertex2i(xc-y, yc+x); 
    glVertex2i(xc+y, yc-x); 
    glVertex2i(xc-y, yc-x); 

  glEnd();

  glFlush();
}
 
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D(-100, 100, -100, 100);

  int xc = -25, yc = 50, r = 40;


  int x = 0, y = r; 
  int d = 3 - 2 * r; 
  drawCircle(xc, yc, x, y);

  while (y >= x) 
  { 
    x++; 
    if (d > 0) 
    { 
      y--; 
      d = d + 4 * (x - y) + 10; 
    } 
    else
      d = d + 4 * x + 6; 
    drawCircle(xc, yc, x, y); 
  }
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");
   glutInit(&argc, argv);
   glutCreateWindow("Bresenham circle algorithm");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);
   initGL();                       
   glutMainLoop();                 
   return 0;
}