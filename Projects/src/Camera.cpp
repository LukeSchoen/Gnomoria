#include "Camera.h"
#include "Renderer.h"
#include "Transform.h"
#include "SDL_keycode.h"

static cam *instance;

cam::cam(Vec3 Pos)
{
  x = Pos.x;
  y = Pos.y;
  z = Pos.z;
}

cam *cam::GetInstance()
{
  if (!instance)
    instance = new cam(Vec3(0, 0, 0));
  return instance;
}

void cam::UpdateKeyboardControls(const unsigned char *keyboard)
{
  float MoveSpeed = y * 0.03f;

  // movement speed
  if (keyboard[SDL_SCANCODE_LSHIFT]) MoveSpeed *= 2;
  if (keyboard[SDL_SCANCODE_LCTRL]) MoveSpeed /= 2;

  if (keyboard[SDL_SCANCODE_W]) z -= MoveSpeed;
  if (keyboard[SDL_SCANCODE_S]) z += MoveSpeed;

  if (keyboard[SDL_SCANCODE_A]) x -= MoveSpeed;
  if (keyboard[SDL_SCANCODE_D]) x += MoveSpeed;

  if (keyboard[SDL_SCANCODE_X]) y -= MoveSpeed;
  if (keyboard[SDL_SCANCODE_E]) y += MoveSpeed;
}

void cam::UpdateMouseControls(int mousex, int mousey, bool leftClick, bool rightClick, int scroll)
{
  static bool lastLMouseDown = false;
  static bool lastRMouseDown = false;

  if (leftClick && (!lastLMouseDown))
  {
    Vec3i pos = Transform_ScreenToWorld(Vec2i(mousex, mousey));
    World_SetBlock(pos, 0);
    World_BuildMesh();
  }

  if (rightClick && (!lastRMouseDown))
  {
    Vec3i pos = Transform_ScreenToWorld(Vec2i(mousex, mousey));
    World_SetBlock(pos + Vec3i(0,1,0), 1);    World_BuildMesh();
  }

  lastLMouseDown = leftClick;
  lastRMouseDown = rightClick;

}