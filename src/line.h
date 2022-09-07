#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>
#include <glm/glm.hpp>


struct Line
{
    Line(const glm::vec3 & begin,const glm::vec3 & end)
        : m_begin(begin)
        , m_end(end)
    {

    }

    glm::vec3 m_begin;
    glm::vec3 m_end;

    struct Ray
    {
        Ray(const glm::vec3 & begin, const glm::vec3 & dir)
            : m_begin(begin)
            , m_dir(glm::normalize(dir))

        {

        }
        
        const glm::vec3 & m_begin;
        const glm::vec3 m_dir;

    };


    Ray asRayBegin2End()
    {
        return std::move(Ray(m_begin,m_end - m_begin));
    }

    Ray asRayEnd2Begin()
    {
        return std::move(Ray(m_end,  m_begin - m_end));
    }

};




#endif 