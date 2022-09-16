#include "IntersectionCalculation.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include "axisalignedbox.h"
#include "triangle.h"
#include <array>
#include <vector>
#include <cmath>
#include <float.h>


/// OBB 与 线的求交 
bool Intersect::IntersectObbWithLine(const OBB& obb, const Line& line)
{
#if 0 
    auto ray_1 = line.asRayBegin2End();
    auto ray_2 = line.asRayEnd2Begin();

    // 以OBB创建坐标系 转换成AABB
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
#endif 

    OBB coord(obb.m_pos, obb.m_size, obb.m_u, obb.m_v, obb.m_w);
    auto ray = line.asRay();
    auto res = Intersect::IntersectObbWithRay(coord, ray);
    return  res;
}
    
bool Intersect::IntersectObbWithRay(const OBB& obb, Ray & ray)
{

    auto delta = obb.m_pos - ray.m_begin;
    float t1, t2;
    double minT = DBL_MIN, maxT = DBL_MAX;

    {
        float e = glm::dot(delta, obb.m_u);
        float f = glm::dot(ray.m_dir, obb.m_u);
        if (std::abs(f) > 1e-20)       ///< 是否平行于平面
        {
            t1 = (e + obb.m_size.x / 2.0) / f;
            t2 = (e - obb.m_size.x / 2.0) / f;
            if (t1 > t2)
            {
                auto temp = t1;
                t1 = t2;
                t2 = temp;
            }

            if (t1 > minT)
            {
                minT = t1;
            }
            if (t2 < maxT)
            {
                maxT = t2;
            }
            if (minT > maxT)
            {
                return false;
            }
            if (maxT < 0)
            {
                return false;
            }
        }
        else if (-e - obb.m_size.x / 2.0 > 0 || -e + obb.m_size.x / 2.0 < 0)
        {
            return false;
        }
    }

    {
        float e = glm::dot(delta, obb.m_v);
        float f = glm::dot(ray.m_dir, obb.m_v);
        if (std::abs(f) > 1e-20)
        {
            t1 = (e + obb.m_size.y / 2.0) / f;
            t2 = (e - obb.m_size.y / 2.0) / f;
            if (t1 > t2)
            {
                auto temp = t1;
                t1 = t2;
                t2 = temp;
            }

            if (t1 > minT)
            {
                minT = t1;
            }
            if (t2 < maxT)
            {
                maxT = t2;
            }
            if (minT > maxT)
            {
                return false;
            }
            if (maxT < 0)
            {
                return false;
            }
        }
        else if (-e - obb.m_size.y / 2.0 > 0 || -e + obb.m_size.y / 2.0 < 0)
        {
            return false;
        }
    }

    {
        float e = glm::dot(delta, obb.m_w);
        float f = glm::dot(ray.m_dir, obb.m_w);
        if (std::abs(f) > 1e-20)
        {
            t1 = (e + obb.m_size.z / 2.0) / f;
            t2 = (e - obb.m_size.z / 2.0) / f;
            if (t1 > t2)
            {
                auto temp = t1;
                t1 = t2;
                t2 = temp;
            }

            if (t1 > minT)
            {
                minT = t1;
            }
            if (t2 < maxT)
            {
                maxT = t2;
            }
            if (minT > maxT)
            {
                return false;
            }
            if (maxT < 0)
            {
                return false;
            }
        }
        else if (-e - obb.m_size.z / 2.0 > 0 || -e + obb.m_size.z / 2.0 < 0)
        {
            return false;
        }
    }

    return true;
}

bool Intersect::IntersectAABBWithTriangle(const AABB &aabb, const Triangle &triangle)
{
    // move AABB ro  origin
    auto box = aabb;
    auto trans = glm::mat4(1.0);
    trans = glm::translate(trans,- box.m_center);
    box.updateTransfrom(trans);

    auto tri = triangle;
    tri.updateTransform(trans);

    std::array<glm::vec3,13> projectAxis;

    std::array<glm::vec3,3> aabbAxisVector;  /// 记录AABB盒子的三个面的法线
    {
        aabbAxisVector[0] = glm::vec3(1.0f, 0.0, 0.0);
        aabbAxisVector[1] = glm::vec3(0.0f, 1.0, 0.0);
        aabbAxisVector[2] = glm::vec3(0.0f, 0.0, 1.0);
    }

    std::array<glm::vec3,3> triEdgeVector;  /// 记录AABB盒子的三个面的法线
    {
        triEdgeVector[0] = tri.m_p2 - tri.m_p1;
        triEdgeVector[1] = tri.m_p3 - tri.m_p2;
        triEdgeVector[2] = tri.m_p1 - tri.m_p3;
    }

    auto triangleNormal = tri.m_normal;

    std::array<glm::vec3,3> aabbFaceNormal;
    {
        aabbFaceNormal[0] = glm::vec3(1.0f, 0.0, 0.0);
        aabbFaceNormal[1] = glm::vec3(0.0f, 1.0, 0.0);
        aabbFaceNormal[2] = glm::vec3(0.0f, 0.0, 1.0);
    }

    // 计算 13根 投影轴
    //    for(auto it: std::vector<int>{0,1,2})
    for(const auto & i: {0,1,2})
    {  /// AABB 边
        for(const auto & j: {0,1,2})
        { /// triangle 边
            projectAxis[i*3 + j] = glm::normalize(glm::cross(aabbAxisVector[i], triEdgeVector[j]));
        }
    }
    projectAxis[9] = triangleNormal;
    for(const auto & index: {0,1,2})
    {
        projectAxis[10 + index] = aabbFaceNormal[index];
    }

    // 相交计算
    for(const auto & it: projectAxis)
    {
        auto p_0 = glm::dot(it,tri.m_p1);
        auto p_1 = glm::dot(it,tri.m_p2);
        auto p_2 = glm::dot(it,tri.m_p3);

        const auto half = glm::vec3(0.5 * aabb.m_size.x,0.5 * aabb.m_size.y,0.5 * aabb.m_size.z);
        auto r = half.x * std::abs(dot(aabbAxisVector[0],it)) +
                half.y * std::abs(dot(aabbAxisVector[1],it)) +
                half.z * std::abs(dot(aabbAxisVector[2],it));
        auto min_p = std::min(std::min(p_0,p_1),p_2);
        auto max_p = std::max(std::max(p_0,p_1),p_2);

        if(min_p > r || max_p < -r)
            return false;
    }

    return true;
}



