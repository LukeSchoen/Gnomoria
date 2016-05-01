#include "text.h"
#include "Math/Vector.h"
#include "Renderer.h"
#include "Camera.h"
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

void Text_Draw(char* text, Vec2 pos, float fontSize, bool inWorld)
{
  float fSize = fontSize / 10.0f;
  int len = strlen(text);
  Text_Draw(text, pos, Vec2(len * fSize, fSize), Vec3(1.0,1.0,1.0), inWorld);
}

void Text_Draw(char* text, Vec2 pos, Vec2 size, Vec3 color, bool inWorld)
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
    float Zpos = 0;

    char tc = text[character];
    if (tc == ' ')
      continue;
    else
      tc -= 33;

    int UVX = tc % 32;
    int UVY = tc / 32;

    float U1 = UVX / 32.0f;
    float V1 = UVY / 32.0f;

    float U2 = U1 + 1.0 / 32.0f;
    float V2 = V1 + 1.0 / 32.0f;

    if (!inWorld)
    {
      cam &c = *cam::GetInstance();
      Xpos1 += c.x;
      Xpos2 += c.x;
      Ypos1 += c.z;
      Ypos2 += c.z;
      Zpos = c.y-1.0;
    }

    textMesh->AddQuad
      (
        Vert(
          Vec3(Xpos1, Zpos, Ypos1),
          color,
          Vec2(U1, V1)),
        Vert(
          Vec3(Xpos2, Zpos, Ypos1),
          color,
          Vec2(U2, V1)),
        Vert(
          Vec3(Xpos2, Zpos, Ypos2),
          color,
          Vec2(U2, V2)),
        Vert(
          Vec3(Xpos1, Zpos, Ypos2),
          color,
          Vec2(U1, V2))
      );
  }

  textMesh->UploadToGPU();
  textMesh->Render();
}