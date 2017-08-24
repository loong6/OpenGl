    //
    //  main.cpp
    //
    //
    //  Created by mwl on 2017/8/23.
    //  Copyright © 2017年 loong6. All rights reserved.
    //  VAO VBO EBO ref:http://blog.csdn.net/dcrmg/article/details/53556664
    //

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Shader.hpp"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frameResizeCb(GLFWwindow* win,int width,int height)
{
    std::cout << "width:  " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * win)
{
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);
}

int main(int argc,char ** argv)
{
    using namespace std;
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* win = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if(win == nullptr){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, frameResizeCb);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
        }
    
    glViewport(0,0,800,600);
    
//    Shader shader("/Users/xl/Documents/GitLab/OpenGl/Shader/shader.vertex","/Users/xl/Documents/GitLab/OpenGl/Shader/shader.frag");
    Shader shader("shader.vertex","shader.frag");
    
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    
    unsigned int indices[]={
        0,1,3,
        1,2,3
    };
        //VBO:顶点缓冲对象, 存于显存中  存储坐标 法向量 颜色等数据 具有唯一id
    /**
     顶点缓冲对象VBO是在显卡存储空间中开辟出的一块内存缓存区，用于存储顶点的各类属性信息，如顶点坐标，顶点法向量，顶点颜色数据等。在渲染时，可以直接从VBO中取出顶点的各类属性数据，由于VBO在显存而不是在内存中，不需要从CPU传输数据，处理效率更高。
     
     所以可以理解为VBO就是显存中的一个存储区域，可以保持大量的顶点属性信息。并且可以开辟很多个VBO，每个VBO在OpenGL中有它的唯一标识ID，这个ID对应着具体的VBO的显存地址，通过这个ID可以对特定的VBO内的数据进行存取操作。
     */
    
    
        //VAO:顶点数组对象:保存了所有顶点数据属性的状态结合,它存储了顶点数据的格式以及顶点数据所需的VBO对象的引用（因为每次绘制之前需要绑定顶点的所有信息）
    /**
     VBO保存了一个模型的顶点属性信息，每次绘制模型之前需要绑定顶点的所有信息，当数据量很大时，重复这样的动作变得非常麻烦。VAO可以把这些所有的配置都存储在一个对象中，每次绘制模型时，只需要绑定这个VAO对象就可以了。
     
     VAO是一个保存了所有顶点数据属性的状态结合，它存储了顶点数据的格式以及顶点数据所需的VBO对象的引用。
     
     VAO本身并没有存储顶点的相关属性数据，这些信息是存储在VBO中的，VAO相当于是对很多个VBO的引用，把一些VBO组合在一起作为一个对象统一管理。
     
     执行VAO绑定之后其后的所有VBO配置都是这个VAO对象的一部分，可以说VBO是对顶点属性信息的绑定，VAO是对很多个VBO的绑定。
     
     */
        //EBO 索引缓冲对象
    /**
     索引缓冲对象EBO相当于OpenGL中的顶点数组的概念，是为了解决同一个顶点多次重复调用的问题，可以减少内存空间浪费，提高执行效率。当需要使用重复的顶点时，通过顶点的位置索引来调用顶点，而不是对重复的顶点信息重复记录，重复调用。
     
     EBO中存储的内容就是顶点位置的索引indices，EBO跟VBO类似，也是在显存中的一块内存缓冲器，只不过EBO保存的是顶点的索引。
     
     创建EBO并绑定，用glBufferData（以GL_ELEMENT_ARRAY_BUFFER为参数）把索引存储到EBO中
     */
    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
        //bind the Vertex Array Object first,then bind and set vertex buffer(s),and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        //通知opengl如何解析顶点数据
        //1st 指定顶点属性位置 于顶点着色器中的layout(location=0)对应
        //2nd 顶点属性大小
        //3rd 数据类型
        //4th 是否希望数据被标准化
        //5th 步长  两条顶点属性之间的间隔
        //6th 位置数据在缓冲区起始位置的偏移量
    //位置
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    //颜色
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
        //
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
        //uncomment this call to draw in wireframe polygons
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//default is GL_FILL
    
    while(!glfwWindowShouldClose(win)){
        processInput(win);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);// set bg color
        glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STEMCIL_BUFFER_BIT
        shader.setFloat("xOffset", 0.5f);
        shader.use();
        
        //运行时改变fragment shader 中的uniform变量
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue)/2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
//        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        
        glBindVertexArray(VAO);
        /**
         OpenGL中所有的图形都是通过分解成三角形的方式进行绘制，glDrawArrays函数负责把模型绘制出来，它使用当前激活的着色器，当前VAO对象中的VBO顶点数据和属性配置来绘制出来基本图形。
         第一个参数表示绘制的类型，有三种取值：
         1.GL_TRIANGLES：每三个顶之间绘制三角形，之间不连接；
         2.GL_TRIANGLE_FAN：以V0V1V2,V0V2V3,V0V3V4，……的形式绘制三角形；
         3.GL_TRIANGLE_STRIP：顺序在每三个顶点之间均绘制三角形。这个方法可以保证从相同的方向上所有三角形均被绘制。以V0V1V2,V1V2V3,V2V3V4……的形式绘制三角形；
         第二个参数定义从缓存中的哪一位开始绘制，一般定义为0；
         第三个参数定义绘制的顶点数量；
         */
        glDrawArrays(GL_TRIANGLES,0,6);
        
            //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        /**
         第一个参数指定了要绘制的模式；
         第二个参数指定要绘制的顶点个数；
         第三个参数是索引的数据类型；
         第四个参数是可选的EBO中偏移量设定。
         */
            //        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
        // clear/delete all resources that were allocated
    glfwTerminate();
    return 0;
}
