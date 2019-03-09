//
//  BasicShader1.hpp
//  studyOpenGLWithC++
//
//  Created by caichao on 2018/7/1.
//  Copyright © 2018年 caichao. All rights reserved.
//

#ifndef BasicShader1_hpp
#define BasicShader1_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Program.h"

class BasicShader {
    
    GLFWwindow *m_window;
    tdogl::Program *m_program;
    
public:
    
    BasicShader();
    bool init();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onScrollCallback(GLFWwindow*window,double x ,double y);
    static void errorCallbackFun(int errorCode,const char* desc);
    
};

#endif /* BasicShader1_hpp */
