//
// Created by lejonmcgowan on 10/23/15.
//

#ifndef TESTPROJECT2_LIGHT_H
#define TESTPROJECT2_LIGHT_H

#include <glm/detail/type_vec3.hpp>
#include "shader.h"

enum LightType
{
    Directional,
    Point,
    Spot
};

class Light
{
private:
    //color properties of light. shared by all types
    glm::vec3 ambient,diffuse,specular;
    glm::vec3 contributions;
    //direction light specific
    glm::vec3 direction;
    //for point lights and spotlights
    glm::vec3 position;
    //for point lights
    /*inverse quadratic attenuation. will be calculated based on values from OGRE3D's Wiki
      values are stored as (quadric,linear,constant)*/
    glm::vec3 attenuation;
    float intensity;
    //for spotlights
    float innerCutoffAngle, outerCutoffAngle;
    bool smoothEdges;
private:
    const int id;
//the type to bind
    LightType lightType;
public:
    static int spotID,dirID,pointID;
    //direction light constructor
    Light(LightType lightType, glm::vec3 direction);
    //point light constructor
    Light(LightType lightType, float range = 10, glm::vec3 position = glm::vec3());
    //spotlight constructor
    Light(LightType lightType, float range, float innerCutoffAngle = 60, float outerCutoffAngle = 65);
    ~Light();

    //for attenuation
    void setLightRange();
    //getters/setters
    const glm::vec3 &getAmbient() const
    {
        return ambient;
    }
    void setAmbient(const glm::vec3 &ambient)
    {
        Light::ambient = ambient;
    }
    const glm::vec3 &getDiffuse() const
    {
        return diffuse;
    }
    void setDiffuse(const glm::vec3 &diffuse)
    {
        Light::diffuse = diffuse;
    }
    const glm::vec3 &getSpecular() const
    {
        return specular;
    }
    void setSpecular(const glm::vec3 &specular)
    {
        Light::specular = specular;
    }
    glm::vec3 getContributions() const
    {
        return contributions;
    }
    void setContributions(glm::vec3 intensity)
    {
        Light::contributions = intensity;
    }
    const glm::vec3 &getDirection() const
    {
        return direction;
    }
    void setDirection(const glm::vec3 &direction)
    {
        Light::direction = direction;
    }
    float getOuterCutoff() const
    {
        return outerCutoffAngle;
    }
    void setHardCutoff(float outerCutoff)
    {
        this->outerCutoffAngle = outerCutoff;
    }
    float getInnerCutoff() const
    {
        return innerCutoffAngle;
    }
    void setInnerCutoff(float softCutoff)
    {
        Light::innerCutoffAngle = softCutoff;
    }
    bool isSmoothEdges() const
    {
        return smoothEdges;
    }
    void setSmoothEdges(bool smoothEdges)
    {
        Light::smoothEdges = smoothEdges;
    }

    const LightType &getLightType() const
    {
        return lightType;
    }

    const glm::vec3 &getAttenuation() const
    {
        return attenuation;
    }

    float getIntensity() const
    {
        return intensity;
    }

    void setIntensity(float intensity)
    {
        Light::intensity = intensity;
    }

    const int getID() const
    {
        return id;
    }

};

#endif //TESTPROJECT2_LIGHT_H
