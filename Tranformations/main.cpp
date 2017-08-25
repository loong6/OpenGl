//
//  main.cpp
//  Tranformations
//
//  Created by mwl on 2017/8/24.
//  Copyright © 2017年 loong6. All rights reserved.
//
/**
 矩阵  向量 于数字进行运算  直接作用于每个元素上
 向量点乘  两个向量的模相乘再乘以夹角的余弦值  相当于一条向量在另一条向量上的投影
 向量叉乘  结果是同时正交于两个向量的向量  
    计算方法 ： （意会吧。。。。。。）
        a   d    bf - ce
        b * e  = cd - af
        c   f    ae - bd
 矩阵相乘：👻👻👻👻👻👻👻👻
 限制条件：
    1.乘号左边矩阵的列数等于右边矩阵的行数时  可以相乘
    2.不满足交换律
 方法：
    乘积C的第m行第n列的元素等于矩阵A的第m行的元素与矩阵B的第n列对应元素乘积之和。
 结果
    维度是左边行* 右边列的矩阵
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Shader/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

typedef unsigned int uint;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

float mixValue = 0.2f;

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
    
    if(glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS){
        mixValue += 0.001f;
        if(mixValue >= 1.0f){
            mixValue = 1.0f;
        }
    }
    
    if(glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS){
        mixValue -= 0.001f;
        if(mixValue <=0.0f){
            mixValue = 0.0f;
        }
    }
}

int main(int argc,char ** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texture", nullptr, nullptr);
    if(!window){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameResizeCb);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    Shader shader("transform.vertex","transform.frag");
    
    float vertices[] = {
        // positions          // colors           // texture coords(note that we changed them to 'zoom in' on our texture image)
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    
    uint indices[] = {
        0,1,3,
        1,2,3
    };
    
    uint VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
        //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    
        //color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
        //texture coord attribute
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void *)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    
        //load and create a texture
    uint texture1,texture2;
    
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
        //set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//GL_NEAREST  邻近滤波   GL_LINEAR  线性滤波
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        //load image,create texture and generate mipmaps
    int width , height , nrChannels;
    stbi_set_flip_vertically_on_load(true);
#ifdef __APPLE__
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
#else
    unsigned char *data = stbi_load("../Resources/container.jpg", &width, &height, &nrChannels, 0);
#endif
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
#ifdef __APPLE__
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
#else
    data = stbi_load("../Resources/awesomeface.png", &width, &height, &nrChannels, 0);
#endif
    if (data){
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
            // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);
        
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(0.5f,-0.5f,0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));
        
        shader.setFloat("mixValue", mixValue);
        shader.use();
        
        uint transformLoc = glGetUniformLocation(shader.ID,"transform");
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform));
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    
    glfwTerminate();
    return 0;
}
