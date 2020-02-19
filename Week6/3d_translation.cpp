#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define PI 3.14159265

int x_shift = 0, y_shift = 0, z_shift = 0;
int choice = 1;
int flag = 0;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);                   
   glEnable(GL_DEPTH_TEST);   
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
 }

void drawCube()
{
  int x1 = 100 + x_shift, x2 = -100 + x_shift, x3 = -100 + x_shift, x4 = 100 + x_shift, x5 = 100 + x_shift, x6 = -100 + x_shift, x7 = -100 + x_shift, x8 = 100 + x_shift;
  int y1 = 100 + y_shift, y2 = 100 + y_shift, y3 = -100 + y_shift, y4 = -100 + y_shift, y5 = 100 + y_shift, y6 = 100 + y_shift, y7 = -100 + y_shift, y8 = -100 + y_shift;
  int z1 = 100 + z_shift, z2 = 100 + z_shift, z3 = 100 + z_shift, z4 = 100 + z_shift, z5 = -100 + z_shift, z6 = -100 + z_shift, z7 = -100 + z_shift, z8 = -100 + z_shift;

  printf("%d %d %d %d %d %d %d %d\n", x1, x2, x3, x4, x5, x6, x7, x8);
  printf("%d %d %d %d %d %d %d %d\n", y1, y2, y3, y4, y5, y6, y7, y8);
  printf("%d %d %d %d %d %d %d %d\n", z1, z2, z3, z4, z5, z6, z7, z8);

  glBegin(GL_QUADS);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Front
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3i(x1, y1, z1);
    glVertex3i(x2, y2, z2);
    glVertex3i(x3, y3, z3);
    glVertex3i(x4, y4, z4);
  
    // Back
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3i(x5, y5, z5);
    glVertex3i(x6, y6, z6);
    glVertex3i(x7, y7, z7);
    glVertex3i(x8, y8, z8);
  
    // Top
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3i(x1, y1, z1);
    glVertex3i(x2, y2, z2);
    glVertex3i(x6, y6, z6);
    glVertex3i(x5, y5, z5);
  
    // Bottom
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3i(x3, y3, z3);
    glVertex3i(x4, y4, z4);  
    glVertex3i(x8, y8, z8);
    glVertex3i(x7, y7, z7);
  
    // Left
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3i(x2, y2, z2);
    glVertex3i(x3, y3, z3);
    glVertex3i(x7, y7, z7);
    glVertex3i(x6, y6, z6);
  
    // Right
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3i(x1, y1, z1);
    glVertex3i(x4, y4, z4);
    glVertex3i(x8, y8, z8);  
    glVertex3i(x5, y5, z5);

  glEnd();

  glFlush();
}

void drawPyramid()
{
  int x1 = 100 + x_shift, x2 = -100 + x_shift, x3 = -100 + x_shift, x4 = 100 + x_shift;
  int y1 = -100 + y_shift, y2 = -100 + y_shift, y3 = -100 + y_shift, y4 = -100 + y_shift;
  int z1 = -100 + z_shift, z2 = -100 + z_shift, z3 = 100 + z_shift, z4 = 100 + z_shift;
  int xtip = 0 + x_shift;
  int ytip = 100 + y_shift;
  int ztip = 0 + z_shift;

  glBegin(GL_QUADS);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Front
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3i(x1, y1, z1);
    glVertex3i(x2, y2, z2);
    glVertex3i(x3, y3, z3);
    glVertex3i(x4, y4, z4);
  glEnd();

  glBegin(GL_TRIANGLES);

    glColor3f(1.0f,1.0f,0.0f);
    glVertex3i(x1, y1, z1);
    glVertex3i(x2, y2, z2);
    glVertex3i(xtip, ytip, ztip);

    glColor3f(1.0f,0.0f,1.0f);
    glVertex3i(x2, y2, z2);
    glVertex3i(x3, y3, z3);
    glVertex3i(xtip, ytip, ztip);

    glColor3f(0.0f,1.0f,1.0f);
    glVertex3i(x3, y3, z3);
    glVertex3i(x4, y4, z4);
    glVertex3i(xtip, ytip, ztip);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3i(x4, y4, z4);
    glVertex3i(x1, y1, z1);
    glVertex3i(xtip, ytip, ztip);

  glEnd();

  glFlush();
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glRotatef(45, 1.0f, 1.0f, 0.0f);
  glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);

  if(flag == 1)
  {
    return;
  }
  flag = 1;

  // printf("%d choice\n", choice);
  switch(choice)
  {
    case 1: {
      drawCube();
      x_shift = 0;
      y_shift = 0;
      z_shift = 0;
      drawCube();
      break;
    }
    case 2: {
      drawPyramid();
      x_shift = 0;
      y_shift = 0;
      z_shift = 0;
      drawPyramid();
      break;
    }
  }

  glutSwapBuffers();

  glPopMatrix();
}
 
int main(int argc, char** argv) {

  printf("Enter\n1 for cube\n2 for pyramid\n");
  scanf("%d", &choice);
  printf("Enter how much the x-axis, y-axis and z-axis have to be shifted by\n");
  scanf("%d%d%d", &x_shift, &y_shift, &z_shift);
  // printf("%d%d%d\n", x_shift, y_shift, z_shift);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glEnable(GL_DEPTH_TEST);
  glutCreateWindow("3d_translate");
  glutInitWindowSize(320, 320);
  glutInitWindowPosition(50, 50);

  glutDisplayFunc(display);
  initGL();                       
  glutMainLoop();                 
  return 0;
}






// createMenu(); above glutDisplayFunc(display);

// void createMenu(void){     submenu_id = glutCreateMenu(menu);
//     glutAddMenuEntry("Sphere", 2);
//     glutAddMenuEntry("Cone", 3);
//     glutAddMenuEntry("Torus", 4);
//     glutAddMenuEntry("Teapot", 5);     menu_id = glutCreateMenu(menu);
//     glutAddMenuEntry("Clear", 1);
//     glutAddSubMenu("Draw", submenu_id);
//     glutAddMenuEntry("Quit", 0);     glutAttachMenu(GLUT_RIGHT_BUTTON);
// } 

// Adds menu


// Add it to display function to choose
// if(value == 1){
//     return; //glutPostRedisplay();
//   }else if(value == 2){
//     glPushMatrix();
//     glColor3d(1.0, 0.0, 0.0);
//     glutWireSphere(0.5, 50, 50);
//     glPopMatrix();
//   }else if(value == 3){
//     glPushMatrix();
//     glColor3d(0.0, 1.0, 0.0);
//     glRotated(65, -1.0, 0.0, 0.0);
//     glutWireCone(0.5, 1.0, 50, 50);
//     glPopMatrix();
//   }else if(value == 4){
//     glPushMatrix();
//     glColor3d(0.0, 0.0, 1.0);
//     glutWireTorus(0.3,0.6,100,100);
//     glPopMatrix();
//   }else if(value == 5){
//     glPushMatrix();
//     glColor3d(1.0, 0.0, 1.0);
//     glutSolidTeapot(0.5);
//     glPopMatrix();
//   }