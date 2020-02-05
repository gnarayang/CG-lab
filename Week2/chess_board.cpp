#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void draw(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

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
            glVertex2i(x1, y1);
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
            glVertex2i(x1, y1);
        }
    }

    glEnd();
    glFlush();
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluOrtho2D(-100, 100, -100, 100);

   for(int i = 0; i < 9; i++)
   {
      draw(-40, 40 - i*10, 40, 40 - i*10);
   }

   for(int i = 0; i < 9; i++)
   {
      draw(40 - i*10, 40, 40 - i*10, -40);
   }
}
 
int main(int argc, char** argv) {
   // printf("Enter the ends of the line\n");
   glutInit(&argc, argv);
   glutCreateWindow("Bresenham algorithm");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);
   initGL();                       
   glutMainLoop();                 
   return 0;
}