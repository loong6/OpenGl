#include <iostream>
#include <fstream>
#if （__linux__）
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
using namespace std;

void drawPolyLine()
{
    glClear(GL_COLOR_BUFFER_BIT);

    fstream inStream;
    inStream.open("/mnt/hgfs/Project/OpenGl/data/dino.data", ios::in);
    if (inStream.fail())
    {
        cout << "open file failed" << endl;
        return;
    }

    GLint numpolys, numLines, x, y;
    inStream >> numpolys;
    for (int j = 0; j < numpolys; ++j)
    {
        inStream >> numLines;
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numLines; ++i)
        {
            inStream >> x >> y;
            glVertex2i(x, y);
        }
        glEnd();
    }
    glFlush();
    inStream.close();
}

void myInit()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0f, 0.0, 480.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640.0, 480.0);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("DRAW POLYLINE");
    myInit();
    glutDisplayFunc(drawPolyLine);
    glutMainLoop();
    return 0;
}
