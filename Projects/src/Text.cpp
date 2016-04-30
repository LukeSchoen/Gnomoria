#include "text.h"
#include "Math/Vector.h"
#include "Renderer.h"
#include <string.h>

RenderObject *textMesh;

void Text_Initialize()
{
  textMesh = new RenderObject(0);
  textMesh->AssignTexture("Assets\\Textures\\Font.bmp");
}

void Text_Destroy()
{
  textMesh->Destroy();
}

void Text_Draw(char* text, Vec2 pos, int fontSize)
{
  float fSize = fontSize / 10.0f;
  int len = strlen(text);
  Text_Draw(text, pos, Vec2(len * fSize, fSize));
}

void Text_Draw(char* text, Vec2 pos, Vec2 size)
{
  int len = strlen(text);
  textMesh->ReAllocate(len * 6);
  textMesh->Clear();

  for (int character = 0; character < len; character++)
  {
    float Xpos1 = pos.x + (size.x) * (character / (len + 0.0));
    float Ypos1 = pos.y;
    float Xpos2 = Xpos1 + (size.x) / (len + 0.0);
    float Ypos2 = Ypos1 + size.y;

    char tc = text[character] - 33;

    int UVX = tc % 32;
    int UVY = tc / 32;

    float U1 = UVX / 32.0f;
    float V1 = UVY / 32.0f;

    float U2 = U1 + 1.0 / 32.0f;
    float V2 = V1 + 1.0 / 32.0f;

    textMesh->AddQuad
      (
        Vert(
          Vec3(Xpos1, 0, Ypos1),
          Vec3(1, 1, 1),
          Vec2(U1, V1)),
        Vert(
          Vec3(Xpos2, 0, Ypos1),
          Vec3(1, 1, 1),
          Vec2(U2, V1)),
        Vert(
          Vec3(Xpos2, 0, Ypos2),
          Vec3(1, 1, 1),
          Vec2(U2, V2)),
        Vert(
          Vec3(Xpos1, 0, Ypos2),
          Vec3(1, 1, 1),
          Vec2(U1, V2))
      );
  }

  textMesh->UploadToGPU();
  textMesh->Render();
}