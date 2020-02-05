#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

float scale_factor = 1.0;
float left_eyeball_x, left_eyeball_y = -30;
float right_eyeball_x, right_eyeball_y = -30;
float smile_pos_x = 0.0, smile_pos_y = 0.0;
float initial_angle = 0, rotate = 0;

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

void drawSmilePoints(int xc, int yc, int x, int y) 
{ 
  glBegin(GL_POINTS);

    glVertex2i(xc+x, yc-y); 
    glVertex2i(xc-x, yc-y); 
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

void drawSmile(int xc, int yc, int r)
{
  int x = 0, y = r; 
  int d = 3 - 2 * r; 

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
    drawSmilePoints(xc, yc, x, y); 
  }
}

void drawFace(float x1, float y1)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluOrtho2D(-1000, 1000, -1000, 1000);

  glTranslatef(x1, y1, 0);
  glScalef(scale_factor, scale_factor, scale_factor);

  // Head
  drawCircle(0, 0, 400);

  // Nose
  drawCircle(0, 0, 10);

  // Eyes
  drawCircle(150, 150, 50);
  drawCircle(-150, 150, 50);

  // Eyeballs
  glTranslatef(150, 150, 0);
  glRotatef(initial_angle + rotate, 0, 0, 1);
  drawCircle(0, -30, 20);
  glRotatef(initial_angle + rotate, 0, 0, -1);
  glTranslatef(-150, -150, 0);
  
  glTranslatef(-150, 150, 0);
  glRotatef(initial_angle + rotate, 0, 0, 1);
  drawCircle(0, -30, 20);
  glRotatef(initial_angle + rotate, 0, 0, -1);
  glTranslatef(150, -150, 0);
  // Smile
  drawSmile(0, 0, 200);

  glPopMatrix();
}
 
void display() {
  drawFace(0.0, 0.0);
}

void key(unsigned char key, int x, int y)
{
  if(key == 'a')
  {
    clock_t start_time = clock();
    while (clock() < start_time + 5000);
    rotate += 5;
    drawFace(smile_pos_x, smile_pos_y);
  }
  if(key == 'b')
  {
    clock_t start_time = clock();
    while (clock() < start_time + 5000);
    rotate -= 5;
    drawFace(smile_pos_x, smile_pos_y);
  }
  
  if(key == 'c')
  {
    scale_factor = scale_factor * (10.0/9.0);
    drawFace(smile_pos_x, smile_pos_y);
  }
  if(key == 'd')
  {
    scale_factor = scale_factor * 0.90;
    drawFace(smile_pos_x, smile_pos_y);
  }
  
  if(key == 'e')
  {
    smile_pos_x += 10;
    drawFace(smile_pos_x, smile_pos_y);
  }
  if(key == 'f')
  {
    smile_pos_x -= 10;
    drawFace(smile_pos_x, smile_pos_y);
  }

  if(key == 'r')
  {
    scale_factor = 1.0;
    smile_pos_x = 0;
    rotate = 0;
    drawFace(smile_pos_x, smile_pos_y); 
  }
  if(key == 'x')
  {
    glutDestroyWindow(1);
  }
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");
   glutInit(&argc, argv);
   glutCreateWindow("Bresenham circle algorithm");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);
   glutKeyboardFunc(key);
   initGL();                       
   glutMainLoop();                 
   return 0;
}