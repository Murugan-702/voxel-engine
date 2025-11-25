#include "VoxelEngine.h"

VoxelEngine::VoxelEngine() {
    deltaTime = 0.0f;
    time = 0.0f;
    isRunning = true;

    initWindow();
}

VoxelEngine::~VoxelEngine() {
    glfwTerminate();
}

void VoxelEngine::initWindow() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow((int)WIN_RES.x, (int)WIN_RES.y, "Voxel Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void VoxelEngine::handleEvents() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        isRunning = false;
    }

    if (glfwWindowShouldClose(window)) {
        isRunning = false;
    }
}

void VoxelEngine::update() {
    static float lastFrame = 0.0f;
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    time = currentFrame;

    static int frameCount = 0;
    static float lastTime = 0.0f;
    frameCount++;
    if (currentFrame - lastTime >= 1.0f) {
        glfwSetWindowTitle(window, ("FPS: " + std::to_string(frameCount)).c_str());
        frameCount = 0;
        lastTime += 1.0f;
    }
}

void VoxelEngine::render() {
    glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
}

void VoxelEngine::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
        glfwPollEvents();
    }
}
