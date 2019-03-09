//
//  ReviewCamera.hpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/27.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#ifndef ReviewCamera_hpp
#define ReviewCamera_hpp

#include <stdio.h>

#include "glew.h"
#include "glfw3.h"
#include <stdio.h>
#include "Program.h"
#include "Texture.h"

#include <glm/glm.hpp>


class CameraToy
{
private:
    GLFWwindow *m_window;
    GLuint m_vao;
    GLuint m_vbo;
    tdogl::Program *m_program;
    tdogl::Texture *m_texture;
    glm::mat4 m_camera;
    glm::mat4 m_projection;
    GLfloat m_degree;
    
private:
    bool initlizeGlfw();
    
    void loadTriangleShaderProgram();
    void bindTriangleData();
    void loopRenderTriangle();
    void loadTriangleTexture();
    void genCameraAndProjection();
    void refreshDegree();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onScrollCallback(GLFWwindow*window,double x ,double y);
    static void errorCallbackFun(int errorCode,const char* desc);
    
    
    
public:
    
    void renderTriangle();
    
    
};

#endif /* ReviewCamera_hpp */
