cmake_minimum_required(VERSION 3.11)
project(ass_3)

# directories
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Executable definition and properties
add_executable(${PROJECT_NAME} 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/SceneReader.cpp
    ${SRC_DIR}/Scene.cpp
    ${SRC_DIR}/Light.cpp
    ${SRC_DIR}/Sphere.cpp
    ${SRC_DIR}/Plane.cpp
    ${SRC_DIR}/Ray.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${SRC_DIR}
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

find_package(Boost 1.67 COMPONENTS filesystem REQUIRED)
target_link_libraries(${PROJECT_NAME} Boost::filesystem)

find_package(X11 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})

# GLM
set(GLM_DIR ${LIB_DIR}/glm)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${GLM_DIR})
target_link_libraries(${PROJECT_NAME} glm)

# CImg
set(CIMG_DIR ${LIB_DIR}/CImg)
add_library(CImg INTERFACE)
target_include_directories(CImg INTERFACE ${CIMG_DIR})
target_include_directories(CImg INTERFACE /opt/X11/include)
target_link_libraries(${PROJECT_NAME} CImg)