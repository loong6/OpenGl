#include <iostream>
#include <cmath>
#include <ctime>
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

const int sW = 640;
const int sH = 480;

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4

float angle = 0.0f;

float red = 1.0f, blue = 1.0f, green = 1.0f;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    angle += 10;
    glutSwapBuffers();
}

void processMenuEvents(int option)
{
    switch (option)
    {
    case RED:
        red = 1.0;
        green = blue = 0.0;
        break;
    case BLUE:
        blue = 1.0;
        red = green = 0.0;
        break;
    case GREEN:
        green = 1.0;
        red = blue = 0.0;
        break;
    case WHITE:
        red = green = blue = 1.0f;
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(sW, sH);
    glutCreateWindow("Menu Test");
    glutDisplayFunc(renderScene);

    glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("White", WHITE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
