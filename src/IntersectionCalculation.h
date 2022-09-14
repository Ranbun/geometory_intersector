#ifndef __INTERSECTION_CALCULATION_H__
#define __INTERSECTION_CALCULATION_H__

#include <iostream>
#include "obb.h"
#include "line.h"
#include "triangle.h"

class AABB;

class Intersect
{
public:
    static bool IntersectObbWithLine(const OBB& obb, const Line& line);
    static bool IntersectObbWithTriangle(const OBB& obb, const Triangle& triangle);
    static bool IntersectAABBWithTriangle(const AABB & obb, const Triangle& triangle);

private:
    static bool IntersectObbWithRay(const OBB& obb, Line::Ray& ray);

};

#endif // !__INTERSECTION_CALCULATION_H__

