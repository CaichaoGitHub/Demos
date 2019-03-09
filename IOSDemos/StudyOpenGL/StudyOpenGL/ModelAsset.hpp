//
//  ModelAsset.hpp
//  StudyOpenGL
//
//  Created by Caichao on 2017/5/27.
//  Copyright © 2017年 Caichao. All rights reserved.
//

#ifndef ModelAsset_hpp
#define ModelAsset_hpp

#include <stdio.h>

#include "glew.h"
#include "glfw3.h"
#include <stdio.h>
#include "Program.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include "Camera.h"
#include <list>
#include "BaseObject.hpp"

//struct ModelAsset {
//    tdogl::Program *shaders;
//    tdogl::Texture *texture;
//    GLuint vbo;
//    GLuint vao;
//    GLenum drawType;
//    GLint drawStart;
//    GLint drawCount;
//    
//    ~ ModelAsset()
//    {
//        //delete shaders;
//        //delete texture;
//    }
//    
//    ModelAsset() :
//    shaders(NULL),
//    texture(NULL),
//    vbo(0),
//    vao(0),
//    drawType(GL_TRIANGLES),
//    drawStart(0),
//    drawCount(0)
//    {}
//};
//
//struct ModelInstance {
//    ModelAsset *asset;
//    glm::mat4 transform;
//    ModelInstance() :
//    asset(NULL),
//    transform()
//    {}
//};

class ModelToy
{
private:
    GLFWwindow *m_window;

    tdogl::Camera m_camera;
    GLfloat m_degree;
    
    std::list<ModelInstance> m_instances;
    ModelAsset m_woodenCrate;
    
private:
    bool initlizeGlfw();
    
    void loopRenderTriangle();
    void refreshCamera(float secondsEsapsed);
    
    void loadWoodenCrateAsset();
    void loadInstances();
    void renderInstances(const ModelInstance &instance);
    void render();
    
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onScrollCallback(GLFWwindow*window,double x ,double y);
    static void errorCallbackFun(int errorCode,const char* desc);
    
    
    
public:
    
    void renderTriangle();
    
    ModelToy();
    
};


#endif /* ModelAsset_hpp */
