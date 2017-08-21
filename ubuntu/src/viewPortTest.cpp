#include <iostream>
#include <cmath>
#if （__linux__）
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#else
#include <GLUT/glut.h>
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#endif

using namespace std;

const float PI = 3.1415926;
const GLint sW = 640;
const GLint sH = 480;

void setWindow(GLdouble left, GLdouble right, GLdouble buttom, GLdouble top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, buttom, top);
}

void setViewport(GLdouble left, GLdouble right, GLdouble buttom, GLdouble top)
{
    glViewport(left, buttom, right - left, top - buttom);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINE_STRIP);
    for (GLfloat x = -10.0; x < 10.0; x += 0.1)
    {
        if (x == 0.0)
        {
            glVertex2f(0.0, 1.0);
        }
        else
        {
            glVertex2f(x, sin(PI * x) / (PI * x));
        }
    }
    glEnd();
    glFlush();
}

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(2.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(sW, sH);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("The Famous Sinc Function");
    glutDisplayFunc(myDisplay);
    myInit();

    setWindow(-10.0, 10.0, -1.0, 1.0);
    setViewport(0, 640, 0, 480);
    glutMainLoop();
    return 0;
}
