//
//  BasicShader1.cpp
//  studyOpenGLWithC++
//
//  Created by caichao on 2018/7/1.
//  Copyright © 2018年 caichao. All rights reserved.
//

#include "BasicShader1.hpp"

#include <cassert>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <unistd.h>
using namespace std;


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const glm::vec2 SCREEN_SIZE(800, 600);

void BasicShader::errorCallbackFun(int errorCode, const char *desc)
{
    printf("some error of glfw code:%d desc:%s",errorCode,desc);
}

void BasicShader::onScrollCallback(GLFWwindow *window, double x, double y)
{
    
}

void BasicShader::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("cliked key code : %d\n",key);
    if (key == 81)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

BasicShader::BasicShader()
{
    tdogl::Shader vShader = tdogl::Shader::shaderFromFile("/Resource/1v.glsl", GL_VERTEX_SHADER);
    tdogl::Shader fShader = tdogl::Shader::shaderFromFile("/Resource/1f.glsl", GL_FRAGMENT_SHADER);
    getcwd(<#char *#>, <#size_t#>)
    m_program = new tdogl::Program(std::vector<tdogl::Shader>{vShader,fShader});
    
}

bool BasicShader::init()
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
    
    
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return false;
    }
    return true;
}










