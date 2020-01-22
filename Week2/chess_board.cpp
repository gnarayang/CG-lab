#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void draw(double x_1, double y_1, double x_2, double y_2) {
   double dx, dy;
   double step;
   double xinc, yinc;
   dx = x_2 - x_1;
   dy = y_2 - y_1;
   if(abs(dx) > abs(dy))
   {
      step = fabs(dx);
   }
   else
   {
      step = fabs(dy);
   }
   xinc = dx/step;
   yinc = dy/step;

   printf("x1 = %f, x2 = %f, y1 = %f, y2 = %f, dx = %f, dy = %f, step = %f, xinc = %f, yinc = %f", x_1, x_2, y_1, y_2, dx, dy, step, xinc, yinc);

   float x = x_1;
   float y = y_1;
   glBegin(GL_POINTS);
   for(int i = 0; i < step; i++)
   {
      // glColor3f(0.0, 1.0, 0.0);
      glVertex2f(x, y);
      printf("%f %f\n", round(x), round(y));
      x += xinc;
      y += yinc;
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