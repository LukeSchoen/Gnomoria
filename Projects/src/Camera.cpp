#include "Camera.h"
#include "Renderer.h"
#include "Text.h"
#include "Transform.h"
#include "SDL_keycode.h"

#include "PathFinder.h"

//static cam *instance;

cam::cam(Vec3 Pos)
{
  x = Pos.x;
  y = Pos.y;
  z = Pos.z;
}

cam *cam::GetInstance()
{
  static cam *instance;
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



void cam::UpdateMouseControls(Vec2i MousePos, bool leftClick, bool rightClick, int scroll)
{
  static bool lastLMouseDown = false;
  static bool lastRMouseDown = false;

  static RenderObject *selection = nullptr;
  if (!selection)
  {
    selection = new RenderObject(6);
    selection->AssignTexture("Assets\\Textures\\Texture.bmp");
  }
  selection->Clear();

  Vec3i pos = Transform_ScreenToWorld(MousePos);

  if (scroll != 0)
  {
    scrollLayer += scroll;
    z -= scroll;
    World_BuildMesh();
  }

  static char posStr[256];
  sprintf(posStr, "mouse x%d y%d z%d", pos.x, pos.y, pos.z);
  float Aspect = (SCREEN_WIDTH / (SCREEN_HEIGHT + 0.0));
  Text_Draw(posStr, Vec2(-Aspect, -1+0.05), 0.5);

  if (pos != Vec3i(-1, -1, -1))
  {
    World_AddTile(selection, pos.x, pos.y, pos.z, Vec3(1.0, 1.0, 1.0), 4);
    selection->UploadToGPU();
    selection->Render();
  }


  static Vec3i start;
  static Vec3i end;
  static bool started = false;
  static bool ended = false;
  static bool clicked = false;

  if (leftClick && (!lastLMouseDown))
  {
    Debug_Clear();
    started = true;
    start = pos + Vec3i(0, 1, 0);
    clicked = true;
    Debug_AddFloorLine(start - Vec3i(0, 1, 0), Vec3(0.0, 0.0, 1.0));
  }

  if (rightClick && (!lastRMouseDown))
  {
    Debug_Clear();
    ended = true;
    end = pos + Vec3i(0, 1, 0);
    clicked = true;
    Debug_AddFloorLine(end - Vec3i(0, 1, 0), Vec3(1.0, 0.0, 0.0));
  }

  if (clicked & started & ended)
  {
    Debug_Clear();
    //find path
    Path p = findPath(start, end);
    
    //Show path length
    //printf("%d\n",p.length);

    clicked = false;
    //started = false;
    //ended = false;
    Debug_AddFloorLine(start - Vec3i(0, 1, 0), Vec3(0.0, 0.0, 1.0));
    Debug_AddFloorLine(end - Vec3i(0, 1, 0), Vec3(1.0, 0.0, 0.0));
  }


  lastLMouseDown = leftClick;
  lastRMouseDown = rightClick;

}



//void cam::UpdateMouseControls(Vec2i MousePos, bool leftClick, bool rightClick, int scroll)
//{
//  static bool lastLMouseDown = false;
//  static bool lastRMouseDown = false;
//
//  static RenderObject *selection = nullptr;
//  if (!selection)
//  {
//    selection = new RenderObject(6);
//    selection->AssignTexture("Assets\\Textures\\Texture.bmp");
//  }
//  selection->Clear();
//
//  Vec3i pos = Transform_ScreenToWorld(MousePos);
//
//
//  char posStr[256];
//  sprintf(posStr, "%d %d %d", pos.x, pos.y, pos.z);
//
//  Text_Draw(posStr, Vec2(-1, -1), 1);
//
//  World_AddTile(selection, pos.x, pos.y, pos.z, Vec3(1.0, 1.0, 1.0), 4);
//  selection->UploadToGPU();
//  selection->Render();
//
//
//  if (leftClick && (!lastLMouseDown))
//  {
//    Vec3i pos = Transform_ScreenToWorld(MousePos);
//    World_SetBlock(pos, 0);
//    World_BuildMesh();
//  }
//
//  if (rightClick && (!lastRMouseDown))
//  {
//    Vec3i pos = Transform_ScreenToWorld(MousePos);
//    World_SetBlock(pos + Vec3i(0, 1, 0), 1);
//    World_BuildMesh();
//  }
//
//  lastLMouseDown = leftClick;
//  lastRMouseDown = rightClick;
//
//}