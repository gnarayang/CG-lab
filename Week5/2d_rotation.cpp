#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define PI 3.14159265

double x_scale = 1, y_scale = 1, rotation_angle;
int choice;
double x_1, x_2, y_1, y_2, sides, x_center, y_center, radius;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void rotate(double &x, double &y, double rotation_angle)
{
  x = x*cos(rotation_angle*PI/180) - y*sin(rotation_angle*PI/180);
  y = y*cos(rotation_angle*PI/180) + x*sin(rotation_angle*PI/180);
}

void drawLine(int x1,int y1,int x2,int y2)
{

    int dx = x2 - x1;
    int dy = y2- y1;

    int stepx = 1, stepy = 1;

    int fraction = 0, fraction_increment = 0;

    if(dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    if(dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }

    glBegin(GL_POINTS);

    if(dx >= dy) {
        fraction = 2*dy - dx;
        fraction_increment = 2*dy;
        while(x1 <= x2)
        {
            x1 += stepx;
            if(fraction >= 0)
            {
                y1 += stepy;
                fraction -= 2*dx; 
            }

            fraction += fraction_increment;
            glVertex2i(x1 * x_scale, y1 * y_scale);
        }

    } 
    else 
    {
        fraction = 2*dx - dy;
        fraction_increment = 2*dx;
        while(y1 <= y2)
        {
            y1 += stepy;
            if(fraction >= 0) 
            {
                x1 += stepx;
                fraction -= 2*dy;
            }
            fraction += fraction_increment;
            glVertex2i(x1 * x_scale, y1 * y_scale);
        }
    }

    glEnd();
    glFlush();
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

void drawPolygon(int sides)
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_POLYGON);

    for(int i = 0; i < sides; i++)
    {
      double angle = (2*PI*i)/sides + rotation_angle*PI/180;
      int x_point = 100*cos(angle), y_point = 100*sin(angle);
      glVertex2i(x_point, y_point);
    }

  glEnd();

  glFlush();
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluOrtho2D(-1000, 1000, -1000, 1000);

  switch(choice)
  {
    case 1: {
      drawLine(x_1, y_1, x_2, y_2);
      rotate(x_1, y_1, rotation_angle);
      rotate(x_2, y_2, rotation_angle);
      drawLine(x_1, y_1, x_2, y_2);
      break;
    }
    case 2: {
      drawPolygon(sides);
      rotation_angle = 0;
      drawPolygon(sides);
      break;
    }
    case 3: {
      drawCircle(x_center, y_center, radius);
      break;
    }
  }

  glPopMatrix();
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");

  double variable1 = 100, variable2 = 100;
  rotate(variable1, variable2, 45);
  printf("%lf %lf\n", variable1, variable2);

  printf("Enter\n1 for line\n2 for polygon\n3 for circle\n");
  scanf("%d", &choice);
  switch(choice)
  {
    case 1: {
      printf("Enter the end points in format\nx1 y1\nx2 y2\n");
      scanf("%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2);
      printf("Enter the angle in degrees by which the figure is to be rotated by\n");
      scanf("%lf", &rotation_angle);
      break;
    }
    case 2: {
      printf("Enter the number of sides\n");
      scanf("%lf", &sides);
      if(sides < 3)
      {
        printf("The number of sides have to be greater than 2\n");
      }
      printf("Enter the angle in degrees by which the figure is to be rotated by\n");
      scanf("%lf", &rotation_angle);
      break;
    }
    case 3: {
      printf("Enter the x_center, y_center and the radius\n");
      scanf("%lf%lf%lf", &x_center, &y_center, &radius);
      printf("Enter the angle in degrees by which the figure is to be rotated by\n");
      scanf("%lf", &rotation_angle);
      break;
    }
    default: {
      printf("Entered option is not valid\n");
    }
  }
   glutInit(&argc, argv);
   glutCreateWindow("2d_rotation");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);

   glutDisplayFunc(display);
   initGL();                       
   glutMainLoop();                 
   return 0;
}