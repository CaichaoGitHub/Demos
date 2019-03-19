//
// Created by caichao on 2019-03-10.
//

#ifndef GLDEMOS_BILLBOARDTECHNIQUE_H
#define GLDEMOS_BILLBOARDTECHNIQUE_H

#include "../common/technique.h"
#include <glm/glm.hpp>

class BillboardTechnique : public Technique{
public:
    BillboardTechnique();
    virtual bool Init();
    void SetVP(const glm::mat4 &vp);
    void SetCameraPosition(const glm::vec3 &pos);
    void SetColorTextureUnit(unsigned int unit);
    void SetBillboardSize(float billboardsize);

private:
    GLuint vplocation_;
    GLuint cameraPosLocation_;
    GLuint colorMapLocation_;
    GLuint billboardSizeLocation_;
};


#endif //GLDEMOS_BILLBOARDTECHNIQUE_H
