//
// Created by caichao on 2019-03-10.
//

#include "BillboardTechnique.h"
#include "../common/ogldev_util.h"

BillboardTechnique::BillboardTechnique()
{
}


bool BillboardTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "billboard.vs")) {
        return false;
    }

    if (!AddShader(GL_GEOMETRY_SHADER, "billboard.gs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "billboard.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    vplocation_ = GetUniformLocation("gVP");
    cameraPosLocation_ = GetUniformLocation("gCameraPos");
    colorMapLocation_ = GetUniformLocation("gColorMap");
    billboardSizeLocation_ = GetUniformLocation("gBillboardSize");

    if (vplocation_ == INVALID_UNIFORM_LOCATION ||
        cameraPosLocation_ == INVALID_UNIFORM_LOCATION ||
        billboardSizeLocation_ == INVALID_UNIFORM_LOCATION ||
        colorMapLocation_ == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return GLCheckError();
}


void BillboardTechnique::SetVP(const glm::mat4 &vp)
{
    glUniformMatrix4fv(vplocation_, 1, GL_TRUE, (const GLfloat*)&vp[0][0]);
}


void BillboardTechnique::SetCameraPosition(const glm::vec3 &pos)
{
    glUniform3f(cameraPosLocation_, pos.x, pos.y, pos.z);
}


void BillboardTechnique::SetColorTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(colorMapLocation_, TextureUnit);
}


void BillboardTechnique::SetBillboardSize(float BillboardSize)
{
    glUniform1f(billboardSizeLocation_, BillboardSize);
}