#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
const int sW = 640;
const int sH = 480;
const double PI = 3.14159265;
GLdouble A, B, C, D;

using namespace std;
void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)sW, 0.0, (GLdouble)sH);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    //公式1
    A = sW / 4.0;
    B = 0.0;
    C = D = sH / 2.0;
    glColor3f(1.0f, 0.0, 0.0);
    for (GLdouble x = 0; x < 4.0; x += 0.005)
    {

        GLdouble func = exp(-x) * cos(2 * PI * x);
        glVertex2d(A * x + B, C * func + D);
    }

    //公式2
    B = sW / 2.0;
    D = sH / 2.0;
    A = sW / (2 * PI);
    C = sH / 2.0f;

    for (GLdouble x = -PI; x < PI; x += 0.005)
    {
        GLdouble func = sin(x);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(A * x + B, C * func + D);

        glColor3f(0.0, 1.0, 1.0);
        func = sin(2 * x);
        glVertex2d(A * x + B, C * func + D);
    }

    B = sW / 2.0f;
    D = sH / 2.0f;
    A = sW / (2.0f * PI);
    C = sH / 2.0f;
    glColor3f(0.0, 0.0, 1.0f);
    for (GLdouble a = 0; a < 2 * PI; a += 0.005)
    {
        GLdouble x = 10 + sin(15 * a);
        GLdouble y = sin(a);
        printf("(%f,%f)\n", A * x + B, C * y + D);
        glVertex2d(A * x + B, C * y + D);
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(sW, sH);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("dot plot of a function");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}