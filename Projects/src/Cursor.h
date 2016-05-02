#ifndef Cursor_h__
#define Cursor_h__

#include "renderer.h"
#include "Math/Vector.h"

enum cursorTypes
{
  normal,
  selectable,
};

void Cursor_DrawCursor(Vec2i mousePos, float cursorSize, cursorTypes cursorType = normal)
{
  static RenderObject *CursorMesh = nullptr;

  if (!CursorMesh)
  {
    CursorMesh = new RenderObject(6);
    CursorMesh->AssignTexture("Assets\\Textures\\Cursor.bmp");
  }

  CursorMesh->Clear();

  float Aspect = SCREEN_WIDTH / (SCREEN_HEIGHT+0.0);
  float xpos = 0 - Aspect + (mousePos.x / (SCREEN_WIDTH + 0.0)) * (Aspect * 2);
  float ypos = 0-1 + mousePos.y / (SCREEN_HEIGHT * 0.5);
  float size = cursorSize*0.1;

  float camXpos = cam::GetInstance()->x;
  float camYpos = cam::GetInstance()->y - 1;
  float camZpos = cam::GetInstance()->z;

  Vert a(Vec3(camXpos + xpos, camYpos, camZpos + ypos), Vec3(1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f));
  Vert b(Vec3(camXpos + xpos + size, camYpos, camZpos + ypos), Vec3(1.0f, 1.0f, 1.0f), Vec2(1 / 16.0f, 0.0f));
  Vert c(Vec3(camXpos + xpos + size, camYpos, camZpos + ypos + size), Vec3(1.0f, 1.0f, 1.0f), Vec2(1 / 16.0f, 1 / 16.0f));
  Vert d(Vec3(camXpos + xpos, camYpos, camZpos + ypos + size), Vec3(1.0f, 1.0f, 1.0f), Vec2(0.0f, 1 / 16.0f));

  CursorMesh->AddQuad(a, b, c, d);

  CursorMesh->UploadToGPU();

  CursorMesh->Render();
}

#endif // Cursor_h__
