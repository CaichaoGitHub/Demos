//
//  Review.hpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/26.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#ifndef Review_hpp
#define Review_hpp


#include "glew.h"
#include "glfw3.h"
#include <stdio.h>
#include "Program.h"
#include "Texture.h"


class RenderToy
{
private:
    GLFWwindow *m_window;
    GLuint m_vao;
    GLuint m_vbo;
    tdogl::Program *m_program;
    tdogl::Texture *m_texture;
    static bool m_exit;
    
private:
    bool initlizeGlfw();
    
    void loadTriangleShaderProgram();
    void bindTriangleData();
    void loopRenderTriangle();
    void loadTriangleTexture();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onScrollCallback(GLFWwindow*window,double x ,double y);
    static void errorCallbackFun(int errorCode,const char* desc);
    
    
    
public:
    
    void renderTriangle();
    
    
};

#endif /* Review_hpp */
