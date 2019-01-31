#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

/**
 * Defines several possible options for camera movement.
 * Used as abstraction to stay away from window-system specific input methods
 */
enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;


/**
 * An abstract camera class that processes input and calculates the
 * corresponding Euler Angles, Vectors and Matrices for use in OpenGL
 */
class Camera {
public:

    /**
     * Constructor with vectors
     */
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    /**
     * Constructor with scalar values
     */
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /**
     * Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
     */
    void processKeyboard(CameraMovement direction, float deltaTime);

    /**
     * Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
     */
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = GL_TRUE);

    /**
     * Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
     */
    void processMouseScroll(float yoffset);

    /**
     *
     * @return Returns the view matrix calculated using Euler Angles and the LookAt Matrix
     */
    glm::mat4 viewMatrix();

    /**
     *
     * @return the zoom
     */
    inline float zoom() const {
        return _zoom;
    };

    /**
     * @return the camera position
     */
    inline glm::vec3 position() const {
        return _position;
    }

private:
    // Camera Attributes
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;

    // Euler Angles
    float _yaw;
    float _pitch;

    // Camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _zoom;

private:
    /**
     * Calculates the front vector from the Camera's (updated) Euler Angles
     */
    void updateCameraVectors();
};
