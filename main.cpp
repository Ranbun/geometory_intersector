#include <iostream>
#include <glm/vec3.hpp>
#include "src/IntersectionCalculation.h"
#include "src/line.h"
#include "src/obb.h"
#include "src/triangle.h"
#include <glm/gtc/matrix_transform.hpp>


int main()
{
    OBB obb(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    Line line(glm::vec3(0, 0, 0), glm::vec3(10.0, 1.0, -5.0));
    Triangle triangle_1(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));
    Triangle triangle_2(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));


    /// TODO OBB 与线的求交
    const auto obbwidthline = Intersect::IntersectObbWithLine(obb, line);

    if(obbwidthline)
    {
        std::cout<< "OBB With Line Intersect"<< std::endl;
    }

    /// OBB 与 三角形的求交
    const auto obbwidthtriangle = Intersect::IntersectObbWithTriangle(triangle_1, triangle_2);

    if(obbwidthtriangle)
    {
        std::cout<< "OBB With Triangle Intersect"<< std::endl;
    }

    return 0;
}