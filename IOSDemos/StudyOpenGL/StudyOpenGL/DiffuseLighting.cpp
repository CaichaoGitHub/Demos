//
//  DiffuseLighting.cpp
//  StudyOpenGL
//
//  Created by caichao on 16/10/6.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#include "DiffuseLighting.hpp"
#include "platform.hpp"

double DiffuseLighting::gScrollY = 0; //static variable should be initilized in source file

DiffuseLighting::DiffuseLighting()
{
    window = nullptr;
    gScrollY = 0;
    degreesRotated = 0;
}

DiffuseLighting::~DiffuseLighting()
{
    
}


tdogl::Program* DiffuseLighting::loadShaders()
{
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("diffuse_point_lighting_vertex_shader.glsl"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("diffuse_point_lighting_fragment_shader.glsl"), GL_FRAGMENT_SHADER));
    return new tdogl::Program(shaders);
}

tdogl::Texture* DiffuseLighting::loadTexture()
{
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath("wooden-crate.jpg"));
    bmp.flipVertically();
    return new tdogl::Texture(bmp);
}

void DiffuseLighting::loadWoodenCrateAsset()
{
    woodenCreate.shaders = loadShaders();
    woodenCreate.drawType = GL_TRIANGLES;
    woodenCreate.drawStart = 0;
    woodenCreate.drawCount = 6*2*3;
    woodenCreate.texture = loadTexture();
    glGenBuffers(1,&woodenCreate.vbo);
    glGenVertexArrays(1,&woodenCreate.vao);
    
    glBindVertexArray(woodenCreate.vao);
    
    glBindBuffer(GL_ARRAY_BUFFER,woodenCreate.vbo);
    
    GLfloat vertexData[] =
    {
        //  X     Y     Z       U     V          Normal
        // bottom
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        
        // top
        -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        
        // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        
        // back
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        
        // left
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        
        // right
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(woodenCreate.shaders->attrib("vert"));
    
    glVertexAttribPointer(woodenCreate.shaders->attrib("vert"),
                          3,
                          GL_FLOAT,GL_FALSE,
                          8*sizeof(GLfloat),
                          NULL);
    
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(woodenCreate.shaders->attrib("vertTexCoord"));
    
    glVertexAttribPointer(woodenCreate.shaders->attrib("vertTexCoord"),
                          2,
                          GL_FLOAT, GL_TRUE,
                          8*sizeof(GLfloat),
                          (const GLvoid*)(3 * sizeof(GLfloat)));
    
    glEnableVertexAttribArray(woodenCreate.shaders->attrib("vertNormal"));
    glVertexAttribPointer(woodenCreate.shaders->attrib("vertNormal"),
                          3,
                          GL_FLOAT,
                          GL_TRUE,
                          8*sizeof(GLfloat),
                          (const GLvoid*)(5 * sizeof(GLfloat)));
    
    // unbind the VAO
    glBindVertexArray(0);
    
}

void DiffuseLighting::createInstance()
{
    ModelInstance dot;
    
    dot.asset = &woodenCreate;
    dot.transform = glm::mat4();
    instance.push_back(dot);
    
    ModelInstance i;
    i.asset = &woodenCreate;
    i.transform = translate(0,-4,0) * scale(1,2,1);
    instance.push_back(i);
    
    ModelInstance hLeft;
    hLeft.asset = &woodenCreate;
    hLeft.transform = translate(-8,0,0) * scale(1,6,1);
    instance.push_back(hLeft);
    
    ModelInstance hRight;
    hRight.asset = &woodenCreate;
    hRight.transform = translate(-4,0,0) * scale(1,6,1);
    instance.push_back(hRight);
    
    ModelInstance hMid;
    hMid.asset = &woodenCreate;
    hMid.transform = translate(-6,0,0) * scale(2,1,0.8f);
    instance.push_back(hMid);
}

void DiffuseLighting::renderInstance(const ModelInstance &inst)
{
    ModelAsset *asset = inst.asset;
    tdogl::Program* shaders = asset->shaders;
    
    shaders->use();
    
    shaders->setUniform("camera", camera.matrix());
    shaders->setUniform("model", inst.transform);
    shaders->setUniform("tex", 0);
    shaders->setUniform("light.position", light.position);
    shaders->setUniform("light.intensities", light.intensities);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset->texture->object());
    
    glBindVertexArray(asset->vao);
    
    glDrawArrays(asset->drawType, asset->drawStart, asset->drawCount);
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shaders->stopUsing();
}

void DiffuseLighting::render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    std::list<ModelInstance>::const_iterator it;
    
    for (it = instance.begin(); it != instance.end(); ++it)
    {
        renderInstance(*it);
    }
    
    glfwSwapBuffers(window);
}

void DiffuseLighting::update(float secondsElapsed)
{
    //rotate the first instance in `gInstances`
    const GLfloat degreesPerSecond = 180.0f;
    degreesRotated += secondsElapsed * degreesPerSecond;
    while(degreesRotated > 360.0f) degreesRotated -= 360.0f;
    instance.front().transform = glm::rotate(glm::mat4(), glm::radians(degreesRotated), glm::vec3(0,1,0));
    
    //move position of camera based on WASD keys, and XZ keys for up and down
    const float moveSpeed = 2.0; //units per second
    if(glfwGetKey(window, 'S')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -camera.forward());
    } else if(glfwGetKey(window, 'W')){
        camera.offsetPosition(secondsElapsed * moveSpeed * camera.forward());
    }
    if(glfwGetKey(window, 'A')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -camera.right());
    } else if(glfwGetKey(window, 'D')){
        camera.offsetPosition(secondsElapsed * moveSpeed * camera.right());
    }
    if(glfwGetKey(window, 'Z')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -glm::vec3(0,1,0));
    } else if(glfwGetKey(window, 'X')){
        camera.offsetPosition(secondsElapsed * moveSpeed * glm::vec3(0,1,0));
    }
    
    //move light
    if(glfwGetKey(window, '1'))
        light.position = camera.position();
    
    // change light color
    if(glfwGetKey(window, '2'))
        light.intensities = glm::vec3(1,0,0); //red
    else if(glfwGetKey(window, '3'))
        light.intensities = glm::vec3(0,1,0); //green
    else if(glfwGetKey(window, '4'))
        light.intensities = glm::vec3(1,1,1); //white
    
    //rotate camera based on mouse movement
    const float mouseSensitivity = 0.1f;
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    camera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
    glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
    
    //increase or decrease field of view based on mouse wheel
    const float zoomSensitivity = -0.2f;
    float fieldOfView = camera.fieldOfView() + zoomSensitivity * (float)gScrollY;
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    camera.setFieldOfView(fieldOfView);
    gScrollY = 0;
}

void DiffuseLighting::onScroll(GLFWwindow *window, double deltax, double deltay)
{
    gScrollY += deltay;
}

void DiffuseLighting::onError(int errorCode, const char *msg)
{
    throw std::runtime_error(msg);
}

void DiffuseLighting::appMain()
{
    glfwSetErrorCallback(onError);
    if (!glfwInit())
    {
        throw std::runtime_error("glfwInit failed");
    }
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "OpenGL Tutorial", NULL, NULL);
    if(!window)
    {
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, 0, 0);
    
    glfwSetScrollCallback(window, onScroll);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("glewInit failed");
    }
    
    while (glGetError() != GL_NO_ERROR)
    {
        
    }
    
    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    if (!GLEW_VERSION_3_2)
    {
        throw std::runtime_error("opengl 3.2 is not avaliable");
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    loadWoodenCrateAsset();
    
    createInstance();
    
    camera.setPosition(glm::vec3(-4,0,17));
    camera.setViewportAspectRatio(SCREEN_SIZE.x/SCREEN_SIZE.y);
    camera.setNearAndFarPlanes(0.5f, 100.f);
    
    light.position = camera.position();
    light.intensities = glm::vec3(1,1,1);
    
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        double thisTime = glfwGetTime();
        update(thisTime - lastTime);
        lastTime = thisTime;
        
        render();
        
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "open gl error" << error << std::endl;
        }
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    
    glfwTerminate();
}
