#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>
#include <glm/glm.hpp>

struct Ray
{
    Ray(const glm::vec3& begin, const glm::vec3& dir)
        : m_begin(begin)
        , m_dir(glm::normalize(dir))
    {}

    glm::vec3 m_begin;
    glm::vec3 m_dir;

};

struct Line
{
    Line(const glm::vec3 & begin,const glm::vec3 & end)
        : m_begin(begin)
        , m_end(end)
    {

    }

    glm::vec3 m_begin;
    glm::vec3 m_end;


    Ray asRayBegin2End() const
    {
        return std::move(Ray(m_begin,m_end - m_begin));
    }

    Ray asRayEnd2Begin() const
    {
        return std::move(Ray(m_end,  m_begin - m_end));
    }

    Ray asRay() const
    {
        return std::move(Ray(m_begin, m_end - m_begin));
    }

};




#endif 