//
// Created by caichao on 2019-03-10.
//

#include "PSUpateTechnique.h"
#include "../common/ogldev_util.h"

PSUpateTechnique::PSUpateTechnique()
{

}

bool PSUpateTechnique::Init()
{
    if (!Technique::Init())
    {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER,"ps_update.vs"))
    {
        return false;
    }

    if (!AddShader(GL_GEOMETRY_SHADER,"ps_update.gs"))
    {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER,"ps_update.fs"))
    {
        return false;
    }

    if (!Finalize())
    {
        return false;
    }

    const GLchar *varyings[4];
    varyings[0] = "Type1";
    varyings[1] = "Position1";
    varyings[2] = "Velocity1";
    varyings[3] = "Age1";

    glTransformFeedbackVaryings(m_shaderProg,4,varyings,GL_INTERLEAVED_ATTRIBS);

    if (!Finalize())
    {
        return false;
    }

    deltaTimeMillisLocation_ = GetUniformLocation("gDeltaTimeMills");
    randomTextureLocation_ = GetUniformLocation("gRandomTexture");
    timeLocation_ = GetUniformLocation("gTime");
    launcherLifetimeLocation_ = GetUniformLocation("gLauncherLifetime");
    shellLifeTimeLocation_ = GetUniformLocation("gShellLifetime");
    secondaryShellLifeTimeLocation_ = GetUniformLocation("gSecondaryShellLifetime");

    if (deltaTimeMillisLocation_ == INVALID_UNIFORM_LOCATION)
    {
        return false;
    }
    return true;

}

void PSUpateTechnique::SetTime(int time)
{
    glUniform1f(timeLocation_,(GLfloat)time);
}

void PSUpateTechnique::SetDeltaTimeMillis(unsigned int deltaTimeMillis)
{
    glUniform1f(deltaTimeMillisLocation_,(GLfloat)deltaTimeMillis);
}

void PSUpateTechnique::setRandomTextureUnit(unsigned int unit)
{
    glUniform1i(randomTextureLocation_,unit);
}

void PSUpateTechnique::setLauncherLifetime(float lifeTime)
{
    glUniform1f(launcherLifetimeLocation_,lifeTime);
}

void PSUpateTechnique::setShellLifeTime(float lifeTime)
{
    glUniform1f(shellLifeTimeLocation_,lifeTime);
}

void PSUpateTechnique::setSecondaryShellLifeTime(float lifeTime)
{
    glUniform1f(secondaryShellLifeTimeLocation_,lifeTime);
}








