#include "IntersectionCalculation.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <cmath>


/// OBB �� �ߵ��� 
bool Intersect::IntersectObbWithLine(const OBB& obb, const Line& line)
{

    auto ray_1 = line.asRayBegin2End();
    auto ray_2 = line.asRayEnd2Begin();

    // ��OBB��������ϵ ת����AABB
    glm::mat4 trans(1.0);
    trans = glm::translate(trans, -obb.m_pos);
    glm::mat4 rotate(
        glm::vec4(obb.m_u, 0.0),    /// u
        glm::vec4(obb.m_v, 0.0),   /// v
        glm::vec4(-obb.m_w, 0.0),   /// w
        glm::vec4(vec3(0.0), 1.0)   /// translate
    );

    rotate = glm::transpose(rotate);

    auto obbPos = rotate * trans * glm::vec4(obb.m_pos, 1.0);
    auto obbU = rotate * glm::vec4(obb.m_u, 0.0);
    auto obbV = rotate * glm::vec4(obb.m_v, 0.0);
    auto obbW = rotate * glm::vec4(obb.m_w, 0.0);

    OBB coord(obbPos, obb.m_size, obbU, obbV, obbW);
    coord.m_trans = trans;
    coord.m_rotate = rotate;


    auto res_1 = Intersect::IntersectObbWithRay(coord, ray_1);
    auto res_2 = Intersect::IntersectObbWithRay(coord, ray_2);

    return (res_1 || res_2);
}

/// �������������ε��� 
bool Intersect::IntersectTriangleWithTriangle(const Triangle& obb, const Triangle& triangle)
{
    /// TODO ʵ�ֲ��� 
    // �����ཻ 


    return false;
}

bool Intersect::IntersectObbWithRay(const OBB& obb, Line::Ray& ray)
{

#if  0
    /// TODO ʵ�ֲ���
    // ��Rayת���� OBB������ϵ�� 

    auto trans = glm::translate(glm::mat4(1.0), - ray.m_begin);
    auto rayBegin = trans * glm::vec4(ray.m_begin,1.0);
    rayBegin = obb.m_rotate * rayBegin;
    rayBegin *= glm::translate(trans, ray.m_begin);
    rayBegin *= obb.m_trans;
    ray.m_begin = glm::vec3(rayBegin);
    ray.m_dir *= obb.m_rotate;
    
    // ��OBB & Line ת������OBB����������ϵ�� 
    // �ֱ�����ߵ���������������Ƿ���OBB�ཻ 
    // ֻҪ��һ���������ཻ ���ཻ 
#endif 

    auto delta = obb.m_pos - ray.m_begin;
    float t1, t2, t3, t4, t5, t6;

    {
        float e = glm::dot(obb.m_u, delta);
        float f = glm::dot(ray.m_dir, obb.m_u);

        t1 = (e - (obb.m_pos + obb.m_u).x) / f;
        t2 = (e + (obb.m_pos + obb.m_u).x) / f;

        if (t1 > t2)
        {
            auto temp = t1;
            t1 = t2;
            t2 = temp;
        }
    }

    {
        float e = glm::dot(obb.m_v, delta);
        float f = glm::dot(ray.m_dir, obb.m_v);

        t3 = (e - (obb.m_pos + obb.m_v).y) / f;
        t4 = (e + (obb.m_pos + obb.m_v).y) / f;

        if (t3 > t4)
        {
            auto temp = t3;
            t3 = t4;
            t4 = temp;
        }
    }

    {
        float e = glm::dot(obb.m_w, delta);
        float f = glm::dot(ray.m_dir, obb.m_w);

        t5 = (e - (obb.m_pos + obb.m_w).z) / f;
        t6 = (e + (obb.m_pos + obb.m_w).z) / f;

        if (t5 > t6)
        {
            auto temp = t5;
            t5 = t6;
            t6 = temp;
        }
    }


    auto minT = std::min(std::min(t1, t3), t5);
    auto maxT = std::min(std::min(t2, t4), t6);

    return minT < maxT;
}



