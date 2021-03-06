//
// Created by lejonmcgowan on 6/26/15.
//

#include "BasicBillboardScene.h"
#include "utils/PathFind.h"

#include <iostream>
#include <assert.h>
#include <src/graphics/drawables/PlaneBuffer.h>
#include <src/graphics/drawables/BufferSphere.h>
#include <src/graphics/drawables/BufferCube.h>
#include <src/graphics/TextureManager.h>

GLuint texture;

Drawable *drawableObject, *happyCube;

void BasicBillboardScene::render()
{
    glClearColor(0.2f,0.3f,0.3f,0.6f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assert(checkGLError);

    shaders.setShader("basic");
    shaders.bind();
        TextureManager::bindTextures();
        assert(checkGLError);

        shaders.setUniform("textureColor1", texIndex("wood"));
        shaders.setUniform("textureColor2", texIndex("happy"));
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,1.0f,1.0f));

        shaders.setUniform("model", happyCube->getTransform().getTransformMatrix());
        shaders.setUniform("view", camera.getViewMatrix());
        shaders.setUniform("projection", camera.getPerspectiveMatrix());

        happyCube->render();
        //drawableObject->render();
        TextureManager::unbindTextures();
    shaders.unbind();


}

void BasicBillboardScene::init(GLFWwindow* window) {

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    Scene::init(window);

    Shader basic(findShader("basic.vert"), findShader("basic.frag"));
    Shader basic2(findShader("basic.vert"), findShader("basic2.frag"));
    shaders.addShader("basic",basic);
    shaders.addShader("basic2",basic2);
    shaders.setShader("basic2");

    std::cout << "starting binding"<< std::endl;
    drawableObject = new PlaneBuffer(10,10,10,10);
    happyCube = new BufferSphere(1.0f,20,20);

    TextureManager::addTexture("happy",findAsset("awesomeface.png"));
    TextureManager::addTexture("wood",findAsset("container.jpg"));

    TextureManager::init();

    shaders.bind(); //for nonchanging uniforms
        shaders.setUniform("myColor",glm::vec4(1.0f,1.0f,1.0f,1.0f));
        shaders.setUniform("textureColor",0);
    shaders.unbind();
}

bool cursorEnabled = true;
bool BasicBillboardScene::processKeys(Keyboard &keyboard)
{
    Scene::processKeys(keyboard);
    Camera::WASDMove(camera,keyboard,0.03f);

    if(keyboard.keyPressed('Q'))
    {
        happyCube->getTransform().scaleIncreaseBy(-0.01f);
    }

    if(keyboard.keyPressed('E'))
    {
        happyCube->getTransform().scaleIncreaseBy(0.01f);
    }

    if(keyboard.keyPressed('Z'))
    {
        happyCube->getTransform().rotateBy(glm::vec3(0.0f,-0.1f, 0.0f));
    }

    if(keyboard.keyPressed('X'))
    {
        happyCube->getTransform().rotateBy(glm::vec3(0.0f,0.1f, 0.0f));
    }

    if(keyboard.keyPressed('R'))
    {
        happyCube->getTransform().reset();
    }
    if(keyboard.keyPressed('V'))
    {
        cursorEnabled = !cursorEnabled;
        if(cursorEnabled)
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }

    return true;
}

bool followMouse = true;
bool BasicBillboardScene::processMouse(Mouse &mouse)
{
    if(mouse.getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        followMouse = !followMouse;
    if(followMouse)
    {
        Camera::WASDLook(camera, mouse, 0.01f);
        Camera::FOVScroll(camera, mouse, 0.1f);
    }

    return true;
}