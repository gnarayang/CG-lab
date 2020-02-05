#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float scale_factor = 100.0;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawStar(float x1, float y1)
{
  // glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluOrtho2D(-1000, 1000, -1000, 1000);

  glTranslatef(x1, y1, 0);
  glScalef(scale_factor, scale_factor, scale_factor);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  glBegin(GL_TRIANGLES);
  glVertex2f(1.0, -1.0);
  glVertex2f(-1.0, -1.0);
  glVertex2f(0.0, 2.0);

  glVertex2f(1.0, 1.0);
  glVertex2f(-1.0, 1.0);
  glVertex2f(0.0, -2.0);  

  glEnd();
  glPopMatrix();

  glFlush();  
}

void key(unsigned char key, int x, int y)
{
  if(key == 's')
  {
    scale_factor = scale_factor * (4.0/3.0);
    // printf("%f\n", scale_factor);
  }
  if(key == 'r')
  {
    scale_factor = scale_factor * 0.75;
    // printf("%f\n", scale_factor);
  }
}

void mouse(int button, int state, int x, int y)
{
  if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    float x1 = ((float)x-150.0)*1000.0/150.0;
    float y1 = -((float)y-150.0)*1000.0/150.0;
    // printf("Right mouse button clicked %f %f\n", x1, y1);
    drawStar(x1, y1);
  }

  else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    glutDestroyWindow(1);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluOrtho2D(-1000, 1000, -1000, 1000);

  drawStar(10.0, 10.0);

  glPopMatrix();
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");
   glutInit(&argc, argv);
   glutCreateWindow("Bresenham circle algorithm");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);
   glutKeyboardFunc(key);
   glutMouseFunc(mouse);
   initGL();                       
   glutMainLoop();                 
   return 0;
}