#pragma once

#include <iostream>
#include <math.h>

#include "../libs/glm/glm/glm.hpp"
#include "../src/util/camera_movement.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, 
            float pitch = PITCH);
        ~Camera();

        glm::mat4 getViewMatrix();

        void processKeyboard(Camera_Movement direction, float delta_time);
        void processMouseMovement(float x_offset, float y_offset, 
            bool constrain_pitch = true);
        void processMouseScroll(float y_offset);

        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

    private:
        void updateCameraVectors();
        glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
        void showVector(const char *id, glm::vec3 vec);
};
