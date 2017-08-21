#if （__linux__）
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif


void myInit();
void myDisplay();
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("my first attempt");
    
    myInit();
    
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glBegin(GL_POINTS);
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
