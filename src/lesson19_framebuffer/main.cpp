#include <file.hpp>
#include <image.hpp>
#include <program.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <model.hpp>
#include <framebuffer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>
#include <map>


unsigned int width = 640, height = 480;

// Timekeeping
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// Camera
Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

// Mouse
bool firstMouse = true;
double lastX = width / 2.0;
double lastY = height / 2.0;

// Called every frame
void handleKeyCameraControls(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
    }
}

void mouseCallback(GLFWwindow *, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void mouseScrollCallback(GLFWwindow *, double, double yoffset) {
    camera.processMouseScroll(yoffset);
}

int main() {

    if (!glfwInit()) {
        // Initialization failed
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Specify OpenGL version to use
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL Tutorial", nullptr, nullptr);
    if (!window) {
        // Window or OpenGL context creation failed
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // Position window in the center
    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);

    // Make the context current for this thread
    glfwMakeContextCurrent(window);

    // Load glad
    if (!gladLoadGL()) {
        std::cout << "Could not initialize GLAD" << std::endl;
        return -1;
    }

    // Resize gl viewport on window resize
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // Handle some input (called less frequently)
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            return;
        }
    });

    // Disable mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set mouse callbacks
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);

    // Enable vsync
    glfwSwapInterval(1);


    // Print gl version
    auto version = glGetString(GL_VERSION);
    std::cout << "Using OpenGL version: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);

    Program fbProgram(readFile("basic.vertex.glsl"), readFile("basic.fragment.glsl"));
    Program screenProgram(readFile("simple.vertex.glsl"), readFile("kernel.fragment.glsl"));

    float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
    float planeVertices[] = {
            // positions          // texture Coords
            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
            5.0f, -0.5f, -5.0f, 2.0f, 2.0f
    };

    float quadVertices[] = {
            // positions   // texCoords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
    };

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glBindVertexArray(0);

    // plane VAO
    unsigned int planeVao, planeVbo;
    glGenVertexArrays(1, &planeVao);
    glGenBuffers(1, &planeVbo);
    glBindVertexArray(planeVao);
    glBindBuffer(GL_ARRAY_BUFFER, planeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    // screen quad VAO
    unsigned int quadVao, quadVbo;
    glGenVertexArrays(1, &quadVao);
    glGenBuffers(1, &quadVbo);
    glBindVertexArray(quadVao);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));

    Texture cubeTexture{Image{"resources/container.jpg"}};
    Texture floorTexture{Image{"resources/marble.jpg"}};

    fbProgram.bind();
    fbProgram.setUniform("texture1", 0);

    screenProgram.bind();
    screenProgram.setUniform("texture1", 0);

    // Setup framebuffer
    Framebuffer framebuffer{width, height};
    framebuffer.bind();
    std::cout << "Framebuffer bound: " << framebuffer.bound() << " ready: " << framebuffer.ready() << std::endl;
    assert(framebuffer.ready());


    while (!glfwWindowShouldClose(window)) {
        // Update time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle camera controls
        handleKeyCameraControls(window);

        // Check errors
        int error;
        while ((error = glGetError())) {
            std::cout << "GL error: " << error << std::endl;
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // first pass (Offscreen)
        framebuffer.bind();
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now

        // Draw scene
        {
            fbProgram.bind();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = camera.viewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.zoom()), (float) width / (float) height, 0.1f,
                                                    100.0f);
            fbProgram.setUniform("view", view);
            fbProgram.setUniform("projection", projection);

            // cubes
            glBindVertexArray(cubeVAO);
            glActiveTexture(GL_TEXTURE0);
            cubeTexture.bind();

            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            fbProgram.setUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            fbProgram.setUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // floor
            glBindVertexArray(planeVao);
            floorTexture.bind();
            fbProgram.setUniform("model", glm::mat4(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }

        // second pass (Onscreen)
        Framebuffer::bindDefault();
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenProgram.bind();
        glBindVertexArray(quadVao);
        glActiveTexture(GL_TEXTURE0);
        framebuffer.texture().bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
