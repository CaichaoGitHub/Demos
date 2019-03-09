//
//  MoreLighting.hpp
//  StudyOpenGL
//
//  Created by caichao on 16/10/6.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#ifndef MoreLighting_hpp
#define MoreLighting_hpp

#include <stdio.h>

#include "BaseObject.hpp"

class MoreLighting {
    const glm::vec2 SCREEN_SIZE = glm::vec2(800,600);
    
    GLFWwindow *window;
    static double gScrollY;
    tdogl::Camera camera;
    ModelAsset woodenCreate;
    std::list<ModelInstance> instance;
    GLfloat degreesRotated = 0.0f;
    Light light;
    
public:
    
    MoreLighting();
    ~MoreLighting();
    
    tdogl::Program* loadShaders();
    tdogl::Texture* loadTexture();
    void loadWoodenCrateAsset();
    inline glm::mat4 translate(GLfloat x,GLfloat y,GLfloat z)
    {
        return glm::translate(glm::mat4(), glm::vec3(x,y,z));
    }
    
    inline glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z)
    {
        return glm::scale(glm::mat4(), glm::vec3(x,y,z));
    }
    
    void createInstance();
    void renderInstance(const ModelInstance &inst);
    void render();
    void update(float secondsElapsed);
    static void onScroll(GLFWwindow* window,double deltax,double deltay);
    static void onError(int errorCode,const char* msg);
    void appMain();
};

#endif /* MoreLighting_hpp */
