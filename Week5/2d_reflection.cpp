#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define PI 3.14159265

int x_scale = 1, y_scale = 1;
int choice;
int x_1, x_2, y_1, y_2, sides, x_center, y_center, radius;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
            printf("%d %d\n", x1 * x_scale, y1 * y_scale);
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
            printf("%d %d\n", x1 * x_scale, y1 * y_scale);
        }
    }

    glEnd();
    glFlush();
}

void drawCirclePoints(int xc, int yc, int x, int y) 
{ 
  glBegin(GL_POINTS);

    glVertex2i(xc+x * x_scale, yc+y * y_scale); 
    glVertex2i(xc-x * x_scale, yc+y * y_scale); 
    glVertex2i(xc+x * x_scale, yc-y * y_scale); 
    glVertex2i(xc-x * x_scale, yc-y * y_scale); 
    glVertex2i(xc+y * x_scale, yc+x * y_scale); 
    glVertex2i(xc-y * x_scale, yc+x * y_scale); 
    glVertex2i(xc+y * x_scale, yc-x * y_scale); 
    glVertex2i(xc-y * x_scale, yc-x * y_scale); 

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
      double angle = (2*PI*i)/sides;
      glVertex2i(100*cos(angle) * x_scale, 100*sin(angle) * y_scale);
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
      x_scale = 1;
      y_scale = 1;
      drawLine(x_1, y_1, x_2, y_2);
      break;
    }
    case 2: {
      drawPolygon(sides);
      x_scale = 1;
      y_scale = 1;
      drawPolygon(sides);
      break;
    }
    case 3: {
      drawCircle(x_center, y_center, radius);
      x_scale = 1;
      y_scale = 1;
      drawCircle(x_center, y_center, radius);
      break;
    }
  }

  glPopMatrix();
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");

  printf("Enter\n1 for line\n2 for polygon\n3 for circle\n");
  scanf("%d", &choice);
  switch(choice)
  {
    case 1: {
      printf("Enter the end points in format\nx1 y1\nx2 y2\n");
      scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
      printf("Enter -1 or 1 whether to be rotated by the x axis and y axis \n");
      scanf("%d%d", &x_scale, &y_scale);
      break;
    }
    case 2: {
      printf("Enter the number of sides\n");
      scanf("%d", &sides);
      if(sides < 3)
      {
        printf("The number of sides have to be greater than 2\n");
      }
      printf("Enter -1 or 1 whether to be rotated by the x axis and y axis \n");
      scanf("%d%d", &x_scale, &y_scale);
      break;
    }
    case 3: {
      printf("Enter the x_center, y_center and the radius\n");
      scanf("%d%d%d", &x_center, &y_center, &radius);
      printf("Enter -1 or 1 whether to be rotated by the x axis and y axis \n");
      scanf("%d%d", &x_scale, &y_scale);
      break;
    }
    default: {
      printf("Entered option is not valid\n");
    }
  }
   glutInit(&argc, argv);
   glutCreateWindow("2d_reflection");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);

   glutDisplayFunc(display);
   initGL();                       
   glutMainLoop();                 
   return 0;
}