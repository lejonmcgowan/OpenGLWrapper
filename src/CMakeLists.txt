include_directories(${TESTPROJECT2_SOURCE_DIR})
link_directories(${TESTPROJECT2_BINARY_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
set(GLFW_LIBRARY_FLAGS -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread)

find_package(GLEW REQUIRED)
include_directories(GLEW_INCLDUE_DIRS)

find_package(SOIL REQUIRED)
include_directories(SOIL_INCLDUE_DIRS)

find_package(ANTTWEAKBAR REQUIRED)
if (ANTTWEAKBAR_FOUND)
    include_directories( ${ANT_TWEAK_BAR_INCLUDE_DIR})
    set(LIBRARIES ${ANT_TWEAK_BAR_LIBRARY})
else (ANTTWEAKBAR_FOUND)
    message(STATUS "AntTweakBar not found.")
endif(ANTTWEAKBAR_FOUND)

set(LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARIES})

if (ANTTWEAKBAR_FOUND)
    include_directories( ${ANT_TWEAK_BAR_INCLUDE_DIR})
    set(LIBRARIES ${ANT_TWEAK_BAR_LIBRARY} ${LIBRARIES})
else (ANTTWEAKBAR_FOUND)
    message(STATUS "AntTweakBar not found.")
endif(ANTTWEAKBAR_FOUND)


add_library(src  graphics/shader.cpp  graphics/drawables/BufferObject.cpp graphics/Buffer.cpp
        graphics/Texture.cpp graphics/IndexBuffer.cpp
        graphics/drawables/PlaneBuffer.cpp
        graphics/drawables/PlaneBuffer.h
        graphics/drawables/Drawable.h
        graphics/drawables/BufferSphere.cpp
        graphics/drawables/BufferSphere.h
        graphics/drawables/BufferCube.cpp
        graphics/drawables/BufferCube.h
        graphics/TextureManager.cpp
        graphics/TextureManager.h
        graphics/materials/PhongMaterial.cpp graphics/materials/PhongMaterial.h
        graphics/Light.cpp graphics/Light.h
        graphics/drawables/BufferTeapot.cpp graphics/drawables/BufferTeapot.h
        graphics/drawables/teapotdata.h
        utils/LightHelper.cpp utils/LightHelper.h utils/TweakBarHelper.cpp utils/TweakBarHelper.h
        utils/WindowContexts.cpp utils/WindowContexts.h
        input/Keyboard.cpp input/Keyboard.h input/Keyboard.h input/Mouse.cpp input/Mouse.h
        math/Transform.h math/Camera.h math/mathNothing.cpp math/mathNothing.cpp
        scenes/window.cpp scenes/window.h
        scenes/BasicBillboardScene.cpp scenes/BasicBillboardScene.h
        scenes/LineScene.cpp scenes/LineScene.h
        scenes/LightingBasicScene.cpp scenes/LightingBasicScene.h
        scenes/BasicTriangleScene.cpp scenes/BasicTriangleScene.h
        scenes/SceneIncludes.h scenes/MultipleLightsScene.cpp scenes/MultipleLightsScene.h
        )

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ext ${CMAKE_SOURCE_DIR}/ext/include)

target_link_libraries(src ${LIBRARIES} ${GLFW_LIBRARY_FLAGS} ${GLEW_LIBRARIES})

add_executable(${PROJECT_NAME} _main.cpp)
target_link_libraries(${PROJECT_NAME} src)