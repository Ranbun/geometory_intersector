cmake_minimum_required(VERSION 3.15)

SET(CMAKE_TOOLCHAIN_FILE E:/Github/vcpkg/scripts/buildsystems/vcpkg.cmake)
# SET(CMAKE_TOOLCHAIN_FILE E:/OpenSources/vcpkg/scripts/buildsystems/vcpkg.cmake)
SET(VCPKG_TARGET_TRIPLET "x64-windows")

project(obb_intersect)
set(target_ intersect)

set(CMAKE_CXX_STANDARD 17)

find_package(glm CONFIG REQUIRED)


set(headerFiles 
   src/obb.h
   src/IntersectionCalculation.h
   src/line.h
   src/triangle.h
   src/axisalignedbox.h
)

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
    PRIVATE
    glm::glm
)

