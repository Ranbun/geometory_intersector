#ifndef __OBB_H_
#define __OBB_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include "axisalignedbox.h"

using glm::vec3;

struct OBB
///< 右手系
{
    OBB(const vec3 & pos,const vec3 & size)
        : m_center(pos)
        , m_size(size)
    {
        m_aabb.m_center = pos;
        m_aabb.m_size = size;
    }

    OBB(const vec3& pos, const vec3& size, const vec3& u, const vec3& v, const vec3& w)
        : m_center(pos)
        , m_size(size) 
        , m_u(u)
        , m_v(v)
        , m_w(w)
    {
        m_aabb.m_center = pos;
        m_aabb.m_size = size;
    }

    vec3 m_center{0, 0, 0};   ///< pos
    vec3 m_size{ 0.5,0.5,0.5 };  ///< 长宽高 x = 长 y = 宽 z = 高
    AABB m_aabb;
    vec3 m_u{1,0,0};     ///< x
    vec3 m_v{0,1,0};     ///< y 
    vec3 m_w{0,0,1};     ///< z 

    glm::mat4 m_trans;                   
    glm::mat4 m_rotate;



};


#endif // !__OBB_H_
