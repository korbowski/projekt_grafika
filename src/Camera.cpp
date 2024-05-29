#include "Camera.h"
//#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Konstanty do kontrolowania szybkoœci ruchu kamery
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

Core::Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : Position(startPosition), WorldUp(startUp), Yaw(startYaw), Pitch(startPitch), Front(glm::vec3(0.0f, 0.0f, -1.0f))
{
    updateCameraVectors();
}

glm::mat4 Core::Camera::createPerspectiveMatrix(float zNear, float zFar)
{
    const float frustumScale = 1.1f;
    glm::mat4 perspective;
    perspective[0][0] = frustumScale;
    perspective[1][1] = frustumScale;
    perspective[2][2] = (zFar + zNear) / (zNear - zFar);
    perspective[3][2] = (2 * zFar * zNear) / (zNear - zFar);
    perspective[2][3] = -1;
    perspective[3][3] = 0;

    return perspective;
}

glm::mat4 Core::Camera::createViewMatrix()
{
    glm::vec3 f = glm::normalize(Front);
    glm::vec3 s = glm::normalize(glm::cross(f, WorldUp));
    glm::vec3 u = glm::cross(s, f);

    glm::mat4 view = glm::mat4(1.0f);
    view[0][0] = s.x;
    view[1][0] = s.y;
    view[2][0] = s.z;
    view[0][1] = u.x;
    view[1][1] = u.y;
    view[2][1] = u.z;
    view[0][2] = -f.x;
    view[1][2] = -f.y;
    view[2][2] = -f.z;
    view[3][0] = -glm::dot(s, Position);
    view[3][1] = -glm::dot(u, Position);
    view[3][2] = glm::dot(f, Position);

    return view;
}

void Core::Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}

void Core::Camera::ProcessKeyboardMovement(int direction, float deltaTime)
{
    float velocity = SPEED * deltaTime;
    if (direction == 0) // Forward
        Position += Front * velocity;
    if (direction == 1) // Backward
        Position -= Front * velocity;
    if (direction == 2) // Left
        Position -= Right * velocity;
    if (direction == 3) // Right
        Position += Right * velocity;
}

void Core::Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
