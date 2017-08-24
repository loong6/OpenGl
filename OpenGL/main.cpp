    //
    //  main.cpp
    //  OpenGL
    //
    //  Created by mwl on 2017/8/21.
    //  Copyright © 2017年 loong6. All rights reserved.
    //

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;


void Render(void)
{
    static GLdouble angle = 1.0;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glRotated(++angle,1.0f , 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    {
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    }
    glEnd();
    glFlush();
}

int main(int argc, char ** argv) {
    
    GLFWwindow* win;
    if(!glfwInit()){
        return -1;
    }
    
    win = glfwCreateWindow(640, 480, "OpenGl Base Project", nullptr, nullptr);
    if(!win){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    if(!glewInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    glfwMakeContextCurrent(win);
    
    while(!glfwWindowShouldClose(win)){
        Render();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    
    return 0;
}
