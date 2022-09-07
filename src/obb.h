#ifndef __OBB_H_
#define __OBB_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/vec3.hpp>

using glm::vec3;

struct OBB
{
    OBB(const vec3 & pos,const vec3 & size)
        : m_pos(pos)
        , m_size(size) {}

    OBB(const vec3& pos, const vec3& size, const vec3& u, const vec3& v, const vec3& w)
        : m_pos(pos)
        , m_size(size) 
        , m_u(u)
        , m_v(v)
        , m_w(w)
    {}

    vec3 m_pos{0,0,0};   ///< pos 
    vec3 m_size{ 0.5,0.5,0.5 };  ///< ����ߵ�һ�� x = �� y = �� z = ��
    vec3 m_u{1,0,0};     ///< x 
    vec3 m_v{0,1,0};     ///< y 
    vec3 m_w{0,0,1};     ///< z 

};


#endif // !__OBB_H_
