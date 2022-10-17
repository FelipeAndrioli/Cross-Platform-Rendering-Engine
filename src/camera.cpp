#include "../include/camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), 
    MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {

    std::cout << "Initializing Camera" << std::endl;
    
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    updateCameraVectors();
}

Camera::~Camera() {
    std::cout << "Destroying camera..." << std::endl;
}

void Camera::showVector(const char *id, glm::vec3 vec) {
    // Debug purposes
    std::cout << id << " " << "x -> " << vec.x << " y -> " << vec.y << " z -> " 
        << vec.z << std::endl;
}

glm::mat4 Camera::getViewMatrix() {
    return lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(Camera_Movement direction, float delta_time) {
    float velocity = delta_time * MovementSpeed;

    if (direction == FORWARD) {
        Position += Front * velocity;  
    }
        
    if (direction == BACKWARD) {
        Position -= Front * velocity;
    }

    if (direction == LEFT) {
        Position -= Right * velocity;
    }

    if (direction == RIGHT) {
        Position += Right * velocity;
    }
}

void Camera::processMouseMovement(float x_offset, float y_offset, 
    bool constrain_pitch) {
 
    x_offset *= MouseSensitivity;
    y_offset *= MouseSensitivity;
   
    Yaw += x_offset;
    Pitch += y_offset;

    if (constrain_pitch) {
        if (Pitch > 89.0f) {
            Pitch = 89.0f;
        } 

        if (Pitch < -89.0f) {
            Pitch = -89.0f;
        }
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(float y_offset) {
    Zoom -= y_offset;

    if (Zoom < 1.0f) {
        Zoom = 1.0f;
    }

    if (Zoom > 45.0f) {
        Zoom = 45.0f;
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front)); 
}

glm::mat4 Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
    glm::vec3 z_axis = glm::normalize(position - target);
    glm::vec3 x_axis = glm::normalize(glm::cross(glm::normalize(worldUp), z_axis));
    glm::vec3 y_axis = glm::cross(z_axis, x_axis);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x; 
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = x_axis.x;
    rotation[1][0] = x_axis.y;
    rotation[2][0] = x_axis.z;
    rotation[0][1] = y_axis.x;
    rotation[1][1] = y_axis.y;
    rotation[2][1] = y_axis.z;
    rotation[0][2] = z_axis.x;
    rotation[1][2] = z_axis.y;
    rotation[2][2] = z_axis.z;

    return rotation * translation;
}

