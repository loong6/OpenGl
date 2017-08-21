#include <iostream>
#include <GL/glut.h>

using namespace std;

void drawChessBoard()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4.0f);
    // glBegin(GL_POINTS);
    for (int i = 0; i < 19; ++i)
    {
        for (int j = 0; j < 19; ++j)
        {
            if ((i * 19 + j) % 2 == 1)
            {
                cout << "red" << endl;
                glColor3f(0.6f, 0.6f, 0.6f);
            }
            else
            {
                cout << "green" << endl;
                glColor3f(0.2f, 0.2f, 0.2f);
            }
            glRecti(i * 20, j * 20, 20 + (i * 19 + j) * 20, 20 + (i * 19 + j) * 20);
        }
    }
    // glEnd();
    glFlush();
}

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 380, 0, 380);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(380, 380);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Chess Board");
    myInit();
    glutDisplayFunc(drawChessBoard);

    glutMainLoop();

    return 0;
}
