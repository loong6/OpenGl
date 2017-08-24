//
//  Shader.hpp
//  OpenGL
//
//  Created by mwl on 2017/8/24.
//  Copyright © 2017年 loong6. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    
    Shader(const GLchar* vertexPath,const GLchar* fragmentPath,const char* geometryPath = nullptr);
    
    void use();
    
    void setBool(const std::string &name,bool value) const;
    void setInt(const std::string &name,int value) const;
    void setFloat(const std::string &name,float value) const;
};
#endif /* Shader_hpp */
