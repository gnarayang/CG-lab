#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int x_min, y_min, x_max, y_max;
int x_1, y_1, x_2, y_2, x_3, y_3;

void initGL()
{
    glClearColor(0, 0, 0, 0);
}

int create_code(int x, int y)
{
    int code = 0;
    // ABRL
    code = code*2 + (y > y_max);
    code = code*2 + (y < y_min);
    code = code*2 + (x > x_max);
    code = code*2 + (x < x_min);
    printf("%d code\n", code);
    return code;
}

void clip_line(int x_1, int y_1, int x_2, int y_2, int code1, int code2)
{
    if(code1 & code2)
    {
        x_1 = x_2 = y_1 = y_2 = 0;
    }
    else
    {
        if(code1)
        {
            printf("Code1 not zero\n");
            if(x_1 < x_min)
            {
                if(x_2 - x_1)
                    y_1 = y_1 + (float)(x_min - x_1) * (float)(y_2 - y_1)/(x_2 - x_1);
                x_1 = x_min;
            }
            if(x_1 > x_max)
            {
                if(x_2 - x_1)
                    y_1 = y_1 + (float)(x_max - x_1) * (float)(y_2 - y_1)/(x_2 - x_1);
                x_1 = x_max;   
            }
            if(y_1 < y_min)
            {
                if(y_2 - y_1)
                    x_1 = x_1 + (float)(y_min - y_1) * (float)(x_2 - x_1)/(y_2 - y_1);
                y_1 = y_min;
            }
            if(y_1 > y_max)
            {
                if(y_2 - y_1)
                    x_1 = x_1 + (float)(y_max - y_1) * (float)(x_2 - x_1)/(y_2 - y_1);
                y_1 = y_max;   
            }
            printf("x1 = %d, y1 = %d\n", x_1, y_1);
        }
        if(code2)
        {
            printf("Code2 not zero\n");
            if(x_2 < x_min)
            {
                if(x_2 - x_1)
                    y_2 = y_2 + (float)(x_min - x_2) * (float)(y_2 - y_1)/(x_2 - x_1);
                x_2 = x_min;
            }
            if(x_2 > x_max)
            {
                if(x_2 - x_1)
                    y_2 = y_2 + (float)(x_max - x_2) * (float)(y_2 - y_1)/(x_2 - x_1);
                x_2 = x_max;   
            }
            if(y_2 < y_min)
            {
                if(y_2 - y_1)
                    x_2 = x_2 + (float)(y_min - y_2) * (float)(x_2 - x_1)/(y_2 - y_1);
                y_2 = y_min;
            }
            if(y_2 > y_max)
            {
                if(y_2 - y_1)
                    x_2 = x_2 + (float)(y_max - y_2) * (float)(x_2 - x_1)/(y_2 - y_1);
                y_2 = y_max;   
            }
            printf("x2 = %d, y2 = %d\n", x_2, y_2);
        }
    }
    glVertex2d(x_1, y_1);
    glVertex2d(x_2, y_2);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(-1000, 1000, -1000, 1000);
    int code1 = create_code(x_1, y_1);
    int code2 = create_code(x_2, y_2);
    int code3 = create_code(x_3, y_3);
    glBegin(GL_LINES);

        glVertex2d(x_min, y_min);
        glVertex2d(x_min, y_max);

        glVertex2d(x_max, y_min);
        glVertex2d(x_max, y_max);

        glVertex2d(x_min, y_min);
        glVertex2d(x_max, y_min);

        glVertex2d(x_min, y_max);
        glVertex2d(x_max, y_max);

        clip_line(x_1, y_1, x_2, y_2, code1, code2);
        clip_line(x_2, y_2, x_3, y_3, code2, code3);
        clip_line(x_3, y_3, x_1, y_1, code3, code1);

    glEnd();
    glFlush();
}

int main(int argc, char **argv) 
{
    printf("Enter the co-ordinates of the line as 'x_1 y_1 x_2 y_2 x_3 y_3' format\n");
    scanf("%d%d%d%d%d%d", &x_1, &y_1, &x_2, &y_2, &x_3, &y_3);
    printf("Enter the clipping window is 'x_min y_min x_max y_max' format\n");
    scanf("%d%d%d%d", &x_min, &y_min, &x_max, &y_max);
    glutInit(&argc, argv);
    glutCreateWindow("Line clipping algorithm");
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(320, 320);
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}