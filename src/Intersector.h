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
    static bool IntersectAABBWithTriangle(const AABB & obb, const Triangle& triangle);
    static bool intersectObbWithObb(OBB &first, OBB &second);

private:
    static bool IntersectObbWithRay(const OBB& obb, Ray & ray);
    static bool computerOBBIntersecte(OBB first, OBB second);

};

#endif // !__INTERSECTION_CALCULATION_H__

