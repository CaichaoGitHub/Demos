//
//  CameraGame.cpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/27.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#include "CameraGame.hpp"


#define GLM_FORCE_RADIANS

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
#include <glm/glm.hpp>
//#include "matrix_transform.hpp"
#include "Camera.h"



const glm::vec2 SCREEN_SIZE(800, 600);

CameraGameToy::CameraGameToy()
{
    m_camera.setPosition(glm::vec3(0,0,4));
    m_camera.setViewportAspectRatio(SCREEN_SIZE.x/SCREEN_SIZE.y);
}

bool CameraGameToy::initlizeGlfw()
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
    
    m_window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "StudyOpenGL", NULL, NULL);
    if (!m_window)
    {
        throw std::runtime_error("window create error");
    }
    
    //
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(m_window, 0, 0);
    glfwSetScrollCallback(m_window, onScrollCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return false;
    }
    return true;
}

void CameraGameToy::errorCallbackFun(int errorCode, const char *desc)
{
    printf("some error of glfw code:%d desc:%s",errorCode,desc);
}

void CameraGameToy::onScrollCallback(GLFWwindow *window, double x, double y)
{
    
}

void CameraGameToy::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("cliked key code : %d\n",key);
    if (key == 81)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void CameraGameToy::refreshCamera(float secondsEsapsed)
{
    const GLfloat degreesPreSecond = 20.f;
    m_degree += secondsEsapsed * degreesPreSecond;
    
    while (m_degree > 360.f)
    {
        m_degree -= 360.0f;
    }
    
    const float moveSpeed = .1f;
    if (glfwGetKey(m_window, 'S'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * -m_camera.forward());
    }
    else if (glfwGetKey(m_window, 'W'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * m_camera.forward());
    }
    
    if (glfwGetKey(m_window, 'A'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * -m_camera.right());
    }
    else if (glfwGetKey(m_window, 'D'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * m_camera.right());
    }
    
    if (glfwGetKey(m_window, 'Z'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * -glm::vec3(0,1,0));
    }
    else if (glfwGetKey(m_window, 'X'))
    {
        m_camera.offsetPosition(secondsEsapsed * moveSpeed * glm::vec3(0,1,0));
    }
    
    const float mouseSensitivity = 0.1f;
    double mx,my;
    glfwGetCursorPos(m_window, &mx, &my);
    m_camera.offsetOrientation(mouseSensitivity*mx, mouseSensitivity*my);
    glfwSetCursorPos(m_window, 0, 0);
}

void CameraGameToy::loopRenderTriangle()
{
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(m_window) )
    {
        //glfwSwapBuffers(m_window);
        glfwPollEvents();
        //glfwWaitEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m_program->use();
        
        double thisTime = glfwGetTime();
        refreshCamera(thisTime - lastTime);
        
        // set the "camera" uniform
        m_program->setUniform("camera", m_camera.matrix());
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture->object());
        m_program->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
        //
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_program->stopUsing();
        glfwSwapBuffers(m_window);
        
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "opengl error : " << error << std::endl;
        }
    }
}

void CameraGameToy::renderTriangle()
{
    if (initlizeGlfw())
    {
        loadTriangleTexture();
        loadTriangleShaderProgram();
        bindTriangleData();
        loopRenderTriangle();
    }
}


void CameraGameToy::loadTriangleTexture()
{
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("wooden-crate.jpg"));
    bmp.flipVertically();
    m_texture = new tdogl::Texture(bmp);
}

void CameraGameToy::loadTriangleShaderProgram()
{
    vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("v_camera_game.glsl"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("f_camera_game.glsl"),GL_FRAGMENT_SHADER));
    m_program = new tdogl::Program(shaders);
    
//    m_program->use();
//    
//    //    glm::mat4 projection = glm::perspective(glm::radians(50.f),SCREEN_SIZE.x/SCREEN_SIZE.y,0.1f,10.0f);
//    //    m_program->setUniform("projection", projection);
//    //
//    glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
//    m_program->setUniform("camera", camera);
//    
//    glm::mat4 projection = glm::perspective(glm::radians(50.0f), SCREEN_SIZE.x/SCREEN_SIZE.y, 0.1f, 10.0f);
//    m_program->setUniform("projection", projection);
//    
//    m_program->stopUsing();
}

void CameraGameToy::bindTriangleData()
{
    glGenVertexArrays(1,&m_vao); //生成 VAO
    glBindVertexArray(m_vao); //在显卡分配一段VAO内存绑定到 gVAO指针
    
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo); //在显卡分配一段VBO内存绑定到 gVBO指针 上传内存数据到显存的通道
    
    GLfloat vertexData[] = {
        //  X     Y     Z       U     V
        // bottom
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        
        // top
        -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        
        // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        
        // back
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
        
        // left
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        
        // right
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f
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
