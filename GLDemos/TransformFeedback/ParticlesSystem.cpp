//
// Created by caichao on 2019-03-09.
//

#include "ParticlesSystem.h"
#include <memory>

#define MAX_PARTICLES 1000
#define PARTICLE_LIFETIME 10.0f
#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

struct Particle{
    float type_;
    glm::vec3 pos_;
    glm::vec3 vel_;
    float lifeTimeMillis;
};

ParticlesSystem::ParticlesSystem()
{
    currTFB_ = 1;
    currVB_ = 0;
    isFirst_ = true;
    time_ = 0;
    texture_ = NULL;
};

ParticlesSystem::~ParticlesSystem()
{
    glDeleteTextures(1,texture_);

    if (transformFeedback_[0] != 0)
        glDeleteTransformFeedbacks(2,transformFeedback_);

    if (particlesBuffer_[0] != 0)
        glDeleteBuffers(2,particlesBuffer_);
}

bool ParticlesSystem::InitParticlesSystem(const glm::vec3 &pos)
{
    Particle particles[MAX_PARTICLES];
    memset(particles,0,MAX_PARTICLES);
    particles[0].type_ = PARTICLE_TYPE_LAUNCHER;
    particles[0].pos_ = pos;
    particles[0].vel_ = glm::vec3(0,0.0001f,0);
    particles[0].lifeTimeMillis = 0.0f;

    glGenTransformFeedbacks(2,transformFeedback_);
    glGenBuffers(2,particlesBuffer_);
    for (int i = 0; i < 2; ++i) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,transformFeedback_[i]);
        glBindBuffer(GL_ARRAY_BUFFER,particlesBuffer_[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particles),particles,GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,particlesBuffer_[i]);

        //关联array_buffer 到 transform_buffer
    }






}


void ParticlesSystem::Render(int deltaTimeMillis, const glm::mat4 &VP, const glm::vec3 &cameraPos)
{
    time_ += deltaTimeMillis;

}








