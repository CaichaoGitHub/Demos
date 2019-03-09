//
//  ModelAsset.cpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/27.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#include "ModelAsset.hpp"

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
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"



const glm::vec2 SCREEN_SIZE(800, 600);

ModelToy::ModelToy()
{
    m_camera.setPosition(glm::vec3(-4,0,17));
    m_camera.setViewportAspectRatio(SCREEN_SIZE.x/SCREEN_SIZE.y);
}

bool ModelToy::initlizeGlfw()
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

void ModelToy::errorCallbackFun(int errorCode, const char *desc)
{
    printf("some error of glfw code:%d desc:%s",errorCode,desc);
}

void ModelToy::onScrollCallback(GLFWwindow *window, double x, double y)
{
    
}

void ModelToy::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("cliked key code : %d\n",key);
    if (key == 81)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

// returns a new tdogl::Program created from the given vertex and fragment shader filenames
static tdogl::Program* LoadShaders(const char* vertFilename, const char* fragFilename) {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath(vertFilename), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath(fragFilename), GL_FRAGMENT_SHADER));
    return new tdogl::Program(shaders);
}


// returns a new tdogl::Texture created from the given filename
static tdogl::Texture* LoadTexture(const char* filename) {
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath(filename));
    bmp.flipVertically();
    return new tdogl::Texture(bmp);
}

void ModelToy::loadWoodenCrateAsset()
{
    m_woodenCrate.shaders = LoadShaders("v_asset.glsl", "f_asset.glsl");
    m_woodenCrate.drawType = GL_TRIANGLES;
    m_woodenCrate.drawStart = 0;
    m_woodenCrate.drawCount = 6*2*3;
    m_woodenCrate.texture = LoadTexture("wooden-crate.jpg");
    glGenBuffers(1, &m_woodenCrate.vbo);
    glGenVertexArrays(1, &m_woodenCrate.vao);
    
    // bind the VAO
    glBindVertexArray(m_woodenCrate.vao);
    
    // bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_woodenCrate.vbo);
    
    // Make a cube out of triangles (two triangles per side)
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(m_woodenCrate.shaders->attrib("vert"));
    glVertexAttribPointer(m_woodenCrate.shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(m_woodenCrate.shaders->attrib("vertTexCoord"));
    glVertexAttribPointer(m_woodenCrate.shaders->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    // unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

// convenience function that returns a translation matrix
glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}


// convenience function that returns a scaling matrix
glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}


void ModelToy::loadInstances()
{
    ModelInstance dot;
    dot.asset = &m_woodenCrate;
    dot.transform = glm::mat4();
    m_instances.push_back(dot);
    
    ModelInstance i;
    i.asset = &m_woodenCrate;
    i.transform = translate(0,-4,0) * scale(1,2,1);
    m_instances.push_back(i);
    
    ModelInstance hLeft;
    hLeft.asset = &m_woodenCrate;
    hLeft.transform = translate(-8,0,0) * scale(1,6,1);
    m_instances.push_back(hLeft);
    
    ModelInstance hRight;
    hRight.asset = &m_woodenCrate;
    hRight.transform = translate(-4,0,0) * scale(1,6,1);
    m_instances.push_back(hRight);
    
    ModelInstance hMid;
    hMid.asset = &m_woodenCrate;
    hMid.transform = translate(-6,0,0) * scale(2,1,0.8);
    m_instances.push_back(hMid);
}

void ModelToy::renderInstances(const ModelInstance &instance)
{
    ModelAsset *asset = instance.asset;
    tdogl::Program *shaders = asset->shaders;
    shaders->use();
    
    shaders->setUniform("camera", m_camera.matrix());
    shaders->setUniform("model", instance.transform);
    shaders->setUniform("tex", 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset->texture->object());
    
    glBindVertexArray(asset->vao);
    glDrawArrays(asset->drawType, asset->drawStart, asset->drawCount);
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    shaders->stopUsing();
}

void ModelToy::render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it = m_instances.begin(); it != m_instances.end(); it++) {
        renderInstances(*it);
    }
    glfwSwapBuffers(m_window);
}

void ModelToy::refreshCamera(float secondsEsapsed)
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

void ModelToy::loopRenderTriangle()
{
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(m_window) )
    {
        //glfwSwapBuffers(m_window);
        glfwPollEvents();
        
        double thisTime = glfwGetTime();
        refreshCamera(thisTime - lastTime);
        
        render();
        
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "opengl error : " << error << std::endl;
        }
    }
}

void ModelToy::renderTriangle()
{
    if (initlizeGlfw())
    {
        loadWoodenCrateAsset();
        loadInstances();
        loopRenderTriangle();
    }
}

