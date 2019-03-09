//
//  main.m
//  StudyOpenGL
//
//  Created by Caichao on 16/3/11.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import <Foundation/Foundation.h>

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
//#include <glm/gtc>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Bitmap.h"
#include "Texture.h"
//#include "glm.hpp"
//#include "matrix_transform.hpp"
#include "Camera.h"
#import "Review.hpp"
#include "ReviewCamera.hpp"
#include "CameraGame.hpp"
#include "ModelAsset.hpp"

#include "AssetInstance.hpp"
#include "DiffuseLighting.hpp"
#include "MoreLighting.hpp"


// constants
const glm::vec2 SCREEN_SIZE(800, 600);
GLFWwindow *gWindow = nullptr;
tdogl::Program *gProgram = nullptr;
tdogl::Texture *gTexture = nullptr;
tdogl::Camera gCamera;
GLuint gVAO = 0;
GLuint gVBO = 0;
double gScrollY = 0.0;
GLfloat gDegreesRotated = 0.0f;

void errorfun(int errorCode,const char* desc);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onScroll(GLFWwindow*window,double x ,double y);
void update(float secondsElapsed);

static void loadShaders() //加载 gl shader 显卡将使用的定点着色器和片着色器，使用显卡特定语言编写
{
    vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex-shader.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment-shader.txt"),GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
}

static void loadTriangle() //加载 vao vbo
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return;
    }
    
    glGenVertexArrays(1,&gVAO); //生成 VAO
    glBindVertexArray(gVAO); //在显卡分配一段VAO内存绑定到 gVAO指针
    
    glGenBuffers(1,&gVBO);
    glBindBuffer(GL_ARRAY_BUFFER,gVBO); //在显卡分配一段VBO内存绑定到 gVBO指针 上传内存数据到显存的通道
    
    GLfloat vertexData[] = {
        0.0f, 0.8f,0.0f,
       -0.8f,-0.8f,0.0f,
        0.8f,-0.8f,0.0f
    };
    //将3个定点数据写入VBO（从内存上传数据到显存中）
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
    glEnableVertexAttribArray(gProgram->attrib("vert")); //开启我们自定义的 vertex-shader 用于定点着色
    glVertexAttribPointer(gProgram->attrib("vert"),3,GL_FLOAT,GL_FALSE,0,NULL);
    //第一个参数，gProgram->attrib("vert")，这就是那个需要上传数据的shder变量。在这个例子中，我们需要发数据给vertshader变量。
    //第二个参数，3表明每个顶点需要三个数字。
    //第三个参数，GL_FLOAT说明三个数字是GLfloat类型。这非常重要，因为GLdouble类型的数据大小跟它是不同的。
    //第四个参数，GL_FALSE说明我们不需要对浮点数进行“归一化”，假如我们使用了归一化，那这个值会被限定为最小0，最大1。我们不需要对我们的顶点进行限制，所以这个参数为false。
    //第五个参数，0，该参数可以在顶点之间有间隔时使用，设置参数为0，表示数据之间没有间隔。
    //第六个参数，NULL，假如我们的数据不是从缓冲区头部开始的话，可以设置这个参数来指定。设置该参数为NULL，表示我们的数据从VBO的第一个字节开始。
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

static void Render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //
    glUseProgram(gProgram->object());
    glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
    glfwSwapBuffers(gWindow);
}

void vertexShader()
{
    loadShaders();
    loadTriangle();
    
    while (!glfwWindowShouldClose(gWindow))
    {
        //glfwSwapBuffers(gWindow);
        glfwPollEvents();
        //glfwWaitEvents();
        Render();
    }
}

void textureShader()
{
    {
        std::vector<tdogl::Shader> shaders; //准备gl 的 vbo vao 后面的操作最终反应到显卡里面的这个小程序
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("texture_vertex-shader.txt"), GL_VERTEX_SHADER));
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("texture_fragment-shader.txt"), GL_FRAGMENT_SHADER));
        gProgram = new tdogl::Program(shaders);
    }
    
    {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            return;
        }
        
        glGenVertexArrays(1,&gVAO);
        glBindVertexArray(gVAO);
        
        glGenBuffers(1,&gVBO);
        glBindBuffer(GL_ARRAY_BUFFER,gVBO);
        
        GLfloat vertexData[] = {
            0.0f, 0.8f,0.0f,0.5f,1.0f,
            -0.8f,-0.8f,0.0f,0.0f,0.0f,
            0.8f,-0.8f,0.0f,1.0f,0.0f,
        };
        
        //将我们的数据写到 vbo 缓存
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
        
        //操作我们的显卡小程序设置其输入
        glEnableVertexAttribArray(gProgram->attrib("vert"));
        glVertexAttribPointer(gProgram->attrib("vert"),3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),NULL);
        
        glEnableVertexAttribArray(gProgram->attrib("vertTexCoord"));
        glVertexAttribPointer(gProgram->attrib("vertTexCoord"),2,GL_FLOAT,GL_TRUE,5*sizeof(GLfloat),(const GLvoid*)(3 * sizeof(GLfloat)));
        
        glBindVertexArray(0);
    }
    
    {
        //准备好贴图
        tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("hazard.png"));
        bmp.flipVertically();
        gTexture = new tdogl::Texture(bmp);
    }
    
    {
        while (!glfwWindowShouldClose(gWindow))
        {
            //glfwSwapBuffers(gWindow);
            glfwPollEvents();
            //glfwWaitEvents();
            {
                glClearColor(0, 0, 0, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                
                gProgram->use();
                
                
                //绘制图元
                glActiveTexture(GL_TEXTURE0);
                
                //加载贴图准备绘制
                glBindTexture(GL_TEXTURE_2D, gTexture->object());
                gProgram->setUniform("tex", 0);
                
                //加载vao
                glBindVertexArray(gVAO);
                
                //绘制
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
                gProgram->stopUsing();
                glfwSwapBuffers(gWindow);
            }
        }
    }
}

void matricesShader()
{
    {
        std::vector<tdogl::Shader> shaders; //加载显卡小程序
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("matrices_vertex-shader.txt"), GL_VERTEX_SHADER));
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("matrices_fragment-shader.txt"), GL_FRAGMENT_SHADER));
        gProgram = new tdogl::Program(shaders);
        
        gProgram->use();
        
        glm::mat4 projection = glm::perspective(glm::radians(50.f),SCREEN_SIZE.x/SCREEN_SIZE.y,0.1f,10.0f);
        gProgram->setUniform("projection", projection);
        
        glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
        gProgram->setUniform("camera", camera);
        
        gProgram->stopUsing();
        
    }
    
    {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            return;
        }
        
        // make and bind the VAO
        glGenVertexArrays(1, &gVAO);
        glBindVertexArray(gVAO);
        
        // make and bind the VBO
        glGenBuffers(1, &gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        
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
        glEnableVertexAttribArray(gProgram->attrib("vert"));
        glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
        
        // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
        glEnableVertexAttribArray(gProgram->attrib("vertTexCoord"));
        glVertexAttribPointer(gProgram->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
        
        // unbind the VAO
        glBindVertexArray(0);
    }
    
    {
        tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("wooden-crate.jpg"));
        bmp.flipVertically();
        gTexture = new tdogl::Texture(bmp);
    }
    
    {
        double lastTime = glfwGetTime();
        while (!glfwWindowShouldClose(gWindow))
        {
            //glfwSwapBuffers(gWindow);
            glfwPollEvents();
            //glfwWaitEvents();
            
            double thisTime = glfwGetTime();
            const GLfloat degreesPerSecond = 180.0f;
            gDegreesRotated += ((thisTime-lastTime) * degreesPerSecond);
            while(gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;
            lastTime = thisTime;
            {
                // clear everything
                glClearColor(0, 0, 0, 1); // black
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                // bind the program (the shaders)
                gProgram->use();
                
                // set the "model" uniform in the vertex shader, based on the gDegreesRotated global
                gProgram->setUniform("model", glm::rotate(glm::mat4(), glm::radians(gDegreesRotated), glm::vec3(0,1,0)));
                
                // bind the texture and set the "tex" uniform in the fragment shader
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, gTexture->object());
                gProgram->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
                
                // bind the VAO (the triangle)
                glBindVertexArray(gVAO);
                
                // draw the VAO
                glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
                
                // unbind the VAO, the program and the texture
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
                gProgram->stopUsing();
                
                // swap the display buffers (displays what was just drawn)
                glfwSwapBuffers(gWindow);
            }
        }
    }
}

void cameraShader()
{
    {
        std::vector<tdogl::Shader> shaders;
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("camera_vertex-shader.txt"), GL_VERTEX_SHADER));
        shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("camera_fragment-shader.txt"), GL_FRAGMENT_SHADER));
        gProgram = new tdogl::Program(shaders);
    }
    
    {
        tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("wooden-crate.jpg"));
        bmp.flipVertically();
        gTexture = new tdogl::Texture(bmp);
    }
    
    {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            return;
        }
        
        // make and bind the VAO
        glGenVertexArrays(1, &gVAO);
        glBindVertexArray(gVAO);
        
        // make and bind the VBO
        glGenBuffers(1, &gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        
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
        glEnableVertexAttribArray(gProgram->attrib("vert"));
        glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
        
        // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
        glEnableVertexAttribArray(gProgram->attrib("vertTexCoord"));
        glVertexAttribPointer(gProgram->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
        
        // unbind the VAO
        glBindVertexArray(0);
        
    }
    
    {
        gCamera.setPosition(glm::vec3(0,0,4));
        gCamera.setViewportAspectRatio(SCREEN_SIZE.x/SCREEN_SIZE.y);
    }
    
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(gWindow))
    {
        glfwPollEvents();
        // update the scene based on the time elapsed since last update
        double thisTime = glfwGetTime();
        update((float)(thisTime - lastTime));
        lastTime = thisTime;
        // clear everything
        glClearColor(0, 0, 0, 1); // black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind the program (the shaders)
        gProgram->use();
        
        // set the "camera" uniform
        gProgram->setUniform("camera", gCamera.matrix());
        
        // set the "model" uniform in the vertex shader, based on the gDegreesRotated global
        gProgram->setUniform("model", glm::rotate(glm::mat4(), glm::radians(gDegreesRotated), glm::vec3(0,1,0)));
        
        // bind the texture and set the "tex" uniform in the fragment shader
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gTexture->object());
        gProgram->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
        
        // bind the VAO (the triangle)
        glBindVertexArray(gVAO);
        
        // draw the VAO
        glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
        
        // unbind the VAO, the program and the texture
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        gProgram->stopUsing();
        
        // swap the display buffers (displays what was just drawn)
        glfwSwapBuffers(gWindow);
        
        if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(gWindow, GL_TRUE);
        }
    }
    
}

void update(float secondsElapsed)
{
    //rotate the cube
    const GLfloat degreesPerSecond = 180.0f;
    gDegreesRotated += secondsElapsed * degreesPerSecond;
    while(gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;
    
    //move position of camera based on WASD keys, and XZ keys for up and down
    const float moveSpeed = 2.0; //units per second
    if(glfwGetKey(gWindow, 'S')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.forward());
    } else if(glfwGetKey(gWindow, 'W')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.forward());
    }
    if(glfwGetKey(gWindow, 'A')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.right());
    } else if(glfwGetKey(gWindow, 'D')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.right());
    }
    if(glfwGetKey(gWindow, 'Z')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * -glm::vec3(0,1,0));
    } else if(glfwGetKey(gWindow, 'X')){
        gCamera.offsetPosition(secondsElapsed * moveSpeed * glm::vec3(0,1,0));
    }
    
    //rotate camera based on mouse movement
    const float mouseSensitivity = 0.1f;
    double mouseX, mouseY;
    glfwGetCursorPos(gWindow, &mouseX, &mouseY);
    gCamera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
    glfwSetCursorPos(gWindow, 0, 0); //reset the mouse, so it doesn't go out of the window
    
    //increase or decrease field of view based on mouse wheel
    const float zoomSensitivity = -0.2f;
    float fieldOfView = gCamera.fieldOfView() + zoomSensitivity * (float)gScrollY;
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    gCamera.setFieldOfView(fieldOfView);
    gScrollY = 0;
}

void test1()
{
//    if (!glfwInit())
//    {
//        throw std::runtime_error("gl init failed");
//    }
//    glfwSetErrorCallback(errorfun);
//    
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_PROFILE);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    gWindow = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "StudyOpenGL", NULL, NULL);
//    if (!gWindow)
//    {
//        throw std::runtime_error("window create error");
//    }
//    
//    //
//    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetCursorPos(gWindow, 0, 0);
//    glfwSetScrollCallback(gWindow, onScroll);
//    glfwSetKeyCallback(gWindow, key_callback);
//    
//    glfwMakeContextCurrent(gWindow);
//    glfwSwapInterval(1);
//    
//    
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//    //vertexShader();
//    //textureShader();
//    //matricesShader();
//    cameraShader();
    
    
//    RenderToy toy;
//    toy.renderTriangle();
    
    //CameraToy toy;
    //toy.renderTriangle();
    
    //    CameraGameToy toy;
    //    toy.renderTriangle();
    ModelToy toy;
    toy.renderTriangle();

}

void test2()
{
    AssetDogger dogger;
    dogger.appMain();
}

void test3()
{
    DiffuseLighting light;
    light.appMain();
}

void test4()
{
    MoreLighting light;
    light.appMain();
}

int main(int argc, const char * argv[])
{
    
    //test2();
    //test3();
    //test4();
    test1();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void errorfun(int errorCode,const char* desc)
{
    
}

void onScroll(GLFWwindow*window,double x ,double y)
{
    gScrollY += x;
}
