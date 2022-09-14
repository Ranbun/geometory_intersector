#ifndef __AXISALIGNEDBOX_H__
#define __AXISALIGNEDBOX_H__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct AABB
{
    explicit AABB(const glm::vec3 & center,const glm::vec3 & size)
        : m_center(center)
        , m_size(size)
    {
        
    }

    void updateTransfrom(const glm::mat4 & model)
    {
        m_center = vec3( model * glm::vec4(m_center,1.0));
    }

    glm::vec3 m_center;
    glm::vec3 m_size;
};





#endif 