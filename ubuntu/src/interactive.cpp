#include <iostream>
#if （__linux__）
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <time.h>

#define TYPE 1

using namespace std;

const int sH = 480;
const int sW = 640;

struct GLintPoint
{
    GLint x, y;
};

bool selected = false;

static GLintPoint corners[2];

void drawDot(int, int);
void drawRect(GLintPoint, GLintPoint);
float getRand()
{
    return rand() % 10 / (double)11;
}
void myMouse(int button, int state, int x, int y)
{
// cout << "myMouse----------" << endl;
// cout << "button:" << button << endl;
// cout << "state:" << state << endl;
// cout << "x:" << x << endl;
// cout << "y:" << y << endl;
// cout << "myMouse--------end" << endl;

//左键画点  右键换背景

// if (state == GLUT_DOWN) //鼠标按下
// {
//     if (button == GLUT_LEFT_BUTTON)
//     {
//         drawDot(x, sH - y);
//         glFlush();
//     }
//     else if (button == GLUT_RIGHT_BUTTON)
//     {
//         glClearColor(getRand(), getRand(), getRand(), 0.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glFlush();
//     }
// }

//左键拖拽画矩形  右键清屏
#if (TYPE == 1)
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {

            corners[0] = {x, sH - y};
        }
        else
        {
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
#else
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        corners[0] = {x, sH - y};
        selected = true;
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    glutPostRedisplay();
#endif
}

void myMovedMouse(int x, int y)
{
// cout << "myMovedMouse----------" << endl;
// cout << "x:" << x << endl;
// cout << "y:" << y << endl;
// cout << "myMovedMouse--------end" << endl;
#if (TYPE == 1)
    drawRect(corners[0], {x, sH - y});
#else
    corners[1] = {x, sH - y};
    glutPostRedisplay();
#endif
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    // cout << "myKeyboardFunc----------" << endl;
    // cout << "key:" << key << endl;
    // cout << "x:" << x << endl;
    // cout << "y:" << y << endl;
    // cout << "myKeyboardFunc--------end" << endl;
    switch (key)
    {
    case 'P':
    case 'p':
        drawDot(x, sH - y);
    default:
        break;
    }
}

void drawDot(int x, int y)
{
    glColor3f(getRand(), getRand(), getRand());
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawRect(GLintPoint p1, GLintPoint p2)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(getRand(), getRand(), getRand());
    glLineWidth(2.0f);
    // glBegin(GL_QUADS);
    glRectf(p1.x, p1.y, p2.x, p2.y);
    // glEnd();
    glFlush();
}

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //背景色
    glClear(GL_COLOR_BUFFER_BIT);     //清屏
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, sW, 0.0, sH);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, sW, sH);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(getRand(), getRand(), getRand());
    if (selected)
    {
        glBegin(GL_QUADS);
        glVertex2i(corners[0].x, corners[0].y);
        glVertex2i(corners[0].x, corners[1].y);
        glVertex2i(corners[1].x, corners[1].y);
        glVertex2i(corners[1].x, corners[0].y);
        glEnd();
    }
    glutSwapBuffers(); //交换两个缓冲区指针
}

#if (TYPE == 1)

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Interactive Test Window");

    glutMouseFunc(myMouse);
    glutMotionFunc(myMovedMouse);
    glutKeyboardFunc(myKeyboardFunc);
    // glutPassiveMotionFunc(myMovedMouse);

    myInit();
    srand(time(NULL));
    glutMainLoop();
    return 0;
}
#else
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(sW, sH);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("GLUT_DOUBLE TEST");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, sW, 0, sH);
    glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    srand(time(NULL));

    glClearColor(getRand(), getRand(), getRand(), 0.0f);
    glViewport(0, 0, sW, sH);
    glutMouseFunc(myMouse);
    glutPassiveMotionFunc(myMovedMouse);

    glutDisplayFunc(myDisplay);

    glutMainLoop();
    return 0;
}

#endif
