#include <assert.h>
#include "window.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

Window::Window(int width, int height, std::string name):
    WINDOW_NAME(name),
    WINDOW_WIDTH(width),
    WINDOW_HEIGHT(height)
{
    assert(WINDOW_WIDTH == WindowContexts::WINDOW_WIDTH);
    assert(WINDOW_HEIGHT == WindowContexts::WINDOW_HEIGHT);
}

void Window::init(Scene* scene)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_NAME.c_str(),
                              NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    checkGLError;//gonna get invalid enum. can't do anything about it.

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //for AntTweakBar
    //TwDefine(" GLOBAL fontscaling=2 "); // use large font
    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    TwDefine(" mybar/Rotation axisx=x axisy=y axisz=-z ");  // Permute z axis to get a left-handed coordinate system

    //set all callbacks to direct towards static classes to be used in scenes
    glfwSetKeyCallback(window,&Keyboard::glfwKeyboardCallback);
    glfwSetCursorPosCallback(window,(GLFWcursorposfun)&Mouse::glfwMouseCursorCallback);
    glfwSetMouseButtonCallback(window, &Mouse::glfwMouseButtonCallback);
    glfwSetScrollCallback(window,&Mouse::glfwScrollCallback);
    glfwSetErrorCallback(error_callback);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);

    this->scene = scene;
    this->scene->init(window);
}
void Window::processKeys()
{
    if(keyboard.keyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
}
void Window::run() //timestep
{
    double time; //not used for now, but useful for later when I need time in my scene
    const double timestep = 1 / 60.0f; //for an ideal 60FPS

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double frameTime = currentTime - lastTime;
        if(frameTime > timestep)
        {
            glfwPollEvents();

            processKeys();
            processMouse();

            scene->processKeys(keyboard);
            scene->processMouse(mouse);

            scene->update();
            scene->render();

            glfwSwapBuffers(window);
            lastTime = glfwGetTime();
        }
    }
}

void Window::stop()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::processMouse()
{

}
