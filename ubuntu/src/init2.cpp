
#if （__linux__）
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

void init()
{
    glClearColor(0.1, 0.1, 0.20, 0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    // glutWireTeapot(3);
    glutWireTorus(0.5, 1.5, 2, 3);
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glBegin(GL_POINT);
    glVertex2i(289, 190);
    glVertex2i(320, 128);
    glVertex2i(239, 67);
    glVertex2i(194, 101);
    glVertex2i(129, 83);
    glVertex2i(75, 73);
    glVertex2i(74, 74);
    glVertex2i(20, 10);
    glEnd();
    glutWireSphere(10.0, 2, 3);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGl 3D View");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
