#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int x_1, x_2, y_1, y_2;
int dx, dy;
int step;
int xinc, yinc;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawCirclePoints(int xc, int yc, int x, int y) 
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

void drawCircle(int xc, int yc, int r)
{
  int x = 0, y = r; 
  int d = 3 - 2 * r; 
  drawCirclePoints(xc, yc, x, y);

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
    drawCirclePoints(xc, yc, x, y); 
  }
}

 
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D(-100, 100, -100, 100);

  int xc = -25, yc = 20, r = 20;

  int i = 0;
  int flag = -1;
  while(true)
  {
    
    drawCircle(xc, yc + i, r);
    clock_t start_time = clock();
    while (clock() < start_time + 5000);
    glClear(GL_COLOR_BUFFER_BIT);
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