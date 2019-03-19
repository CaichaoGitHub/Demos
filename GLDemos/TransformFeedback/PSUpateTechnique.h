//
// Created by caichao on 2019-03-10.
//

#ifndef GLDEMOS_PSUPATETECHNIQUE_H
#define GLDEMOS_PSUPATETECHNIQUE_H

#include "../common/technique.h"

class PSUpateTechnique : public  Technique{

public:

    PSUpateTechnique();
    virtual bool Init();
    void SetParticleLifeTime(float lifTime);
    void SetDeltaTimeMillis(unsigned int deltaTimeMillis);
    void SetTime(int time);
    void setRandomTextureUnit(unsigned int unit);
    void setLauncherLifetime(float lifeTime);
    void setShellLifeTime(float lifeTime);
    void setSecondaryShellLifeTime(float lifeTime);

private:
    GLuint deltaTimeMillisLocation_;
    GLuint randomTextureLocation_;
    GLuint timeLocation_;
    GLuint launcherLifetimeLocation_;
    GLuint shellLifeTimeLocation_;
    GLuint secondaryShellLifeTimeLocation_;
};


#endif //GLDEMOS_PSUPATETECHNIQUE_H
