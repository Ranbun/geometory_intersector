#ifndef __OBB_H_
#define __OBB_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

using glm::vec3;

struct OBB  ///< 右手系
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
    vec3 m_size{ 0.5,0.5,0.5 };  ///< 长宽高的一般 x = 长 y = 宽 z = 高
    vec3 m_u{1,0,0};     ///< x 
    vec3 m_v{0,1,0};     ///< y 
    vec3 m_w{0,0,1};     ///< z 

    glm::mat4 m_trans;
    glm::mat4 m_rotate;



};


#endif // !__OBB_H_
