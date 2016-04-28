#include "Camera.h"
#include "Renderer.h"

#include <gtx/rotate_vector.hpp>
#include <gtc/matrix_transform.hpp>
#include "SDL_keycode.h"

glm::vec3 Camera_CameraKeyboardControls(const unsigned char *keyboard)
{
  float MoveSpeed = camPos.y*0.03f;
  glm::vec3 mov(0.0f, 0.0f, 1.0f);
  glm::vec3 finalMov(0.0f, 0.0f, 0.0f);

  // movement speed
  if (keyboard[SDL_SCANCODE_LSHIFT]) MoveSpeed *= 2;
  if (keyboard[SDL_SCANCODE_LCTRL]) MoveSpeed /= 2;


  // Up / Down
  mov = glm::vec3(0.0, -1.0, 0.0);
  mov = glm::rotate(mov, camAng.x, glm::vec3(1.0, 0, 0));
  mov = glm::rotate(mov, camAng.y, glm::vec3(0, 1.0, 0));

  if (keyboard[SDL_SCANCODE_W]) finalMov -= mov;
  if (keyboard[SDL_SCANCODE_S]) finalMov += mov;


  // left / right
  mov = glm::vec3(1.0, 0.0, 0.0);
  mov = glm::rotate(mov, camAng.x, glm::vec3(1.0, 0, 0));
  mov = glm::rotate(mov, camAng.y, glm::vec3(0, 1.0, 0));

  if (keyboard[SDL_SCANCODE_A]) finalMov -= mov;
  if (keyboard[SDL_SCANCODE_D]) finalMov += mov;


  // Towards / Away
  if (keyboard[SDL_SCANCODE_E]) finalMov += glm::vec3(0.0, 1.0, 0.0);
  if (keyboard[SDL_SCANCODE_X]) finalMov -= glm::vec3(0.0, 1.0, 0.0);

  // create and return velocity vector
  if (glm::length(finalMov) >= 0.05)
    finalMov = glm::normalize(finalMov) * MoveSpeed;
  return finalMov;
}

glm::mat4 Camera_GetCameraMatrix()
{
  glm::mat4 cam;
  cam = glm::rotate(cam, -camAng.x, glm::vec3(1.0, 0, 0));
  cam = glm::rotate(cam, -camAng.y, glm::vec3(0, 1.0, 0));
  cam = glm::translate(cam, -camPos);
  return cam;
}