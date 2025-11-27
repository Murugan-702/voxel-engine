#include "VoxelEngine.h"
#include <iostream>
#include "Player.h"
#include "ShaderProgram.h"
#include "Scene.h"
VoxelEngine::VoxelEngine() : deltaTime(0.0f), time(0.0f), lastFrameTime(0.0), isRunning(true)
{
    initWindow();
    initGL();

    player = std::make_shared<Player>(this, PLAYER_POS);
    shaderProgram = std::make_shared<ShaderProgram>(this);
    scene = std::make_shared<Scene>(this);
}

VoxelEngine::~VoxelEngine()
{
    glfwTerminate();
}

void VoxelEngine::initWindow()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow((int)WIN_RES.x, (int)WIN_RES.y, "Voxel Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, (int)WIN_RES.x, (int)WIN_RES.y);
}

void VoxelEngine::initGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
}

void VoxelEngine::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        isRunning = false;

    player->keyboardControl();
}

void VoxelEngine::update()
{

    float currentFrame = glfwGetTime(); // seconds
    deltaTime = currentFrame - lastFrameTime;
    lastFrameTime = currentFrame;
    time = currentFrame;
    static float timer = 0.0f;
    timer += deltaTime;

    processInput();
    player->update();
    shaderProgram->update();
    scene->update();
}

void VoxelEngine::render()
{
    glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->render();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void VoxelEngine::run()
{
    while (isRunning && !glfwWindowShouldClose(window))
    {
        update();
        render();
    }
}
