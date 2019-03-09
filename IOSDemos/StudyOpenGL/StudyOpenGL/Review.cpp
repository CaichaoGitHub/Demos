//
//  Review.cpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/26.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#include "Review.hpp"
//#import <Foundation/Foundation.h>

#include <cassert>
#include <stdexcept>
#include <cmath>
#include <vector>
using namespace std;


#include <iostream>
#include "platform.hpp"
#include "glew.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include "Program.h"
#include "Bitmap.h"
#include "Texture.h"
//#include "matrix_transform.hpp"
#include "Camera.h"


bool RenderToy::initlizeGlfw()
{
    if (!glfwInit())
    {
        throw std::runtime_error("gl init failed");
    }
    glfwSetErrorCallback(errorCallbackFun);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(300, 300, "StudyOpenGL", NULL, NULL);
    if (!m_window)
    {
        throw std::runtime_error("window create error");
    }
    
    //
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(m_window, 0, 0);
   // glfwSetScrollCallback(m_window, onScrollCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    
    
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return false;
    }
    return true;
}

void RenderToy::errorCallbackFun(int errorCode, const char *desc)
{
    printf("some error of glfw code:%d desc:%s",errorCode,desc);
}

void RenderToy::onScrollCallback(GLFWwindow *window, double x, double y)
{
    
}

void RenderToy::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("cliked key code : %d\n",key);
    if (key == 81)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void RenderToy::loopRenderTriangle()
{
    while (!glfwWindowShouldClose(m_window) )
    {
        //glfwSwapBuffers(m_window);
        glfwPollEvents();
        //glfwWaitEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        m_program->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture->object());
        m_program->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
        //
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_program->stopUsing();
        glfwSwapBuffers(m_window);
    }
}

void RenderToy::renderTriangle()
{
    if (initlizeGlfw())
    {
        loadTriangleTexture();
        loadTriangleShaderProgram();
        bindTriangleData();
        loopRenderTriangle();
    }
}

void RenderToy::loadTriangleTexture()
{
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("hazard.png"));
    bmp.flipVertically();
    m_texture = new tdogl::Texture(bmp);
}

void RenderToy::loadTriangleShaderProgram()
{
    vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("v_triangle.glsl"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("f_triangle.glsl"),GL_FRAGMENT_SHADER));
    m_program = new tdogl::Program(shaders);
}

void RenderToy::bindTriangleData()
{
    glGenVertexArrays(1,&m_vao); //生成 VAO
    glBindVertexArray(m_vao); //在显卡分配一段VAO内存绑定到 gVAO指针
    
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo); //在显卡分配一段VBO内存绑定到 gVBO指针 上传内存数据到显存的通道
    
    GLfloat vertexData[] = {
        0.0f, 0.8f,0.0f,0.5f,1.0f,
        -0.8f,-0.8f,0.0f,0.0f,0.0f,
        0.8f,-0.8f,0.0f,1.0f,0.0f,
    };
    //将3个定点数据写入VBO（从内存上传数据到显存中）
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
    glEnableVertexAttribArray(m_program->attrib("vert")); //开启我们自定义的 vertex-shader 用于定点着色
    glVertexAttribPointer(m_program->attrib("vert"),3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),NULL);
    glEnableVertexAttribArray(m_program->attrib("vertTexCoord"));
    glVertexAttribPointer(m_program->attrib("vertTexCoord"),2,GL_FLOAT,GL_TRUE,5*sizeof(GLfloat),(const GLvoid*)(3 * sizeof(GLfloat)));
    //第一个参数，gProgram->attrib("vert")，这就是那个需要上传数据的shder变量。在这个例子中，我们需要发数据给vertshader变量。
    //第二个参数，3表明每个顶点需要三个数字。
    //第三个参数，GL_FLOAT说明三个数字是GLfloat类型。这非常重要，因为GLdouble类型的数据大小跟它是不同的。
    //第四个参数，GL_FALSE说明我们不需要对浮点数进行“归一化”，假如我们使用了归一化，那这个值会被限定为最小0，最大1。我们不需要对我们的顶点进行限制，所以这个参数为false。
    //第五个参数，0，该参数可以在顶点之间有间隔时使用，设置参数为0，表示数据之间没有间隔。
    //第六个参数，NULL，假如我们的数据不是从缓冲区头部开始的话，可以设置这个参数来指定。设置该参数为NULL，表示我们的数据从VBO的第一个字节开始。
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}









