cmake_minimum_required(VERSION 3.15)
project(obb_intersect)
set(target_ intersect)


find_package(glm CONFIG REQUIRED)


set(headerFiles 
   src/obb.h
   src/IntersectionCalculation.h
   src/line.h
   src/triangle.h)

set(sourceFiles 
    main.cpp
    src/IntersectionCalculation.cpp
)


add_executable(${target_} ${sourceFiles} ${headerFiles})

target_include_directories(
${target_}
PRIVATE
${glm_INCLUDE_DIR}
)

target_link_libraries(
    ${target_}
    glm::glm
)

