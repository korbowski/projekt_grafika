#pragma once

#include <glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

namespace Core {
    class Camera {
    public:
        Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);
        glm::mat4 createPerspectiveMatrix(float zNear, float zFar);
        glm::mat4 createViewMatrix();

        void ProcessMouseMovement(float xoffset, float yoffset);
        void ProcessKeyboardMovement(int direction, float deltaTime);

        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

    private:
        void updateCameraVectors();
    };
}
