//
// Created by caichao on 2019-03-09.
//

#ifndef GLDEMOS_PARTICLESSYSTEM_H
#define GLDEMOS_PARTICLESSYSTEM_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class ParticlesSystem {

    class PSUpdateTechnique;
    class BillboardTechnique;
    class RandomTexture;
    class Texture;

public:
    ParticlesSystem();
    ~ParticlesSystem();

    bool InitParticlesSystem(const glm::vec3 &pos);
    void Render(int deltaTimeMillis, const glm::mat4 &VP, const glm::vec3 &cameraPos);

private:

    void UpdateParticles(int deltaTimeMillis);
    void RenderParticles(const glm::mat4 &vp,const glm::vec3 &cameraPos);

    bool isFirst_;
    unsigned int currVB_;
    unsigned int currTFB_;
    GLuint particlesBuffer_[2];
    GLuint transformFeedback_[2];
    PSUpdateTechnique updateTechnique_;
    BillboardTechnique billboardTechnique_;
    RandomTexture randomTexture_;
    Texture texture_;
    int time_;
};


#endif //GLDEMOS_PARTICLESSYSTEM_H
