#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <iostream>
#include <glm/glm.hpp>


struct Triangle
{
    /// ע�������εĶ���˳��Ϊ��ʱ�� 
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
        /// ���������εķ��� 

        /*
                p2   
        

          p3           p1
        
        */

        auto v1 = p3 - p1;
        auto v2 = p2 - p1;
        auto normal = glm::normalize(glm::cross(v2, v1));

    }

    glm::vec3 m_p1;
    glm::vec3 m_p2;
    glm::vec3 m_p3;
    glm::vec3 m_normal;

};




#endif 