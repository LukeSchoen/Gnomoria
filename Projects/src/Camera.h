#ifndef Camera_h__
#define Camera_h__

#include <glm.hpp>

const float Deg2Rag = 1.0f / 57.2958f;

static glm::vec3 camPos(0, 10, 0);
static glm::vec2 camAng(0- Deg2Rag * 90, 0);

glm::vec3 Camera_CameraKeyboardControls(const unsigned char *keyboard);

glm::mat4 Camera_GetCameraMatrix();
#endif // Camera_h__