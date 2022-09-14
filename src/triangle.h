#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>


struct Triangle
{
    /// 注意三角形的顶点顺序为逆时针 
    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& normal)
        : m_p1(p1)
        , m_p2(p2)
        , m_p3(p3)
        , m_normal(glm::normalize(normal))
    {


    }

    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
        : m_p1(p1)
        , m_p2(p2)
        , m_p3(p3)
    {
        /// 计算三角形的法相 

        /*
                p2   
        

          p3           p1
        
        */

        auto v1 = p3 - p1;
        auto v2 = p2 - p1;
        m_normal = glm::normalize(glm::cross(v2, v1));

    }

    void updateTransform(glm::mat4 & model)
    {
        m_p1 = vec3(model * glm::vec4(m_p1,1.0));
        m_p2 = vec3(model * glm::vec4(m_p2,1.0));
        m_p3 = vec3(model * glm::vec4(m_p3,1.0));

        auto v1 = m_p3 - m_p1;
        auto v2 = m_p2 - m_p1;
        m_normal = glm::normalize(glm::cross(v2, v1));
    }

    glm::vec3 m_p1;
    glm::vec3 m_p2;
    glm::vec3 m_p3;
    glm::vec3 m_normal;

};




#endif 