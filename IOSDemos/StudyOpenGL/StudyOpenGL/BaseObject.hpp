//
//  BaseObject.hpp
//  StudyOpenGL
//
//  Created by caichao on 16/10/6.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#ifndef BaseObject_hpp
#define BaseObject_hpp

#include <stdio.h>
#include <list>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>

#include "Program.h"
#include "Texture.h"
#include "Camera.h"

struct ModelAsset {
    tdogl::Program* shaders;
    tdogl::Texture* texture;
    
    GLuint vbo;
    GLuint vao;
    
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
    
    GLfloat shininess;
    glm::vec3 specularColor;
    
    ModelAsset():
    shaders(nullptr),
    texture(nullptr),
    vbo(0),
    vao(0),
    drawType(GL_TRIANGLES),
    drawStart(0),
    drawCount(0),
    shininess(0.0f),
    specularColor(1.0,1.0,1.0)
    {
        
    }
};

struct ModelInstance {
    
    ModelAsset* asset;
    glm::mat4 transform;
    
    ModelInstance():
    asset(nullptr),
    transform()
    {
        
    }
    
};

struct Light {
    glm::vec3 position;
    glm::vec3 intensities;
    float attenuation;
    float ambientCoefficient;
};

#endif /* BaseObject_hpp */
