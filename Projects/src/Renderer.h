#ifndef Renderer_h__
#define Renderer_h__

#include "Math/Vector.h"

const int USE_VSYNC = 1;

#ifdef _DEBUG
//Window resolution
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const bool FULL_SCREEN = false;
#else
#ifdef testWindow
//Window resolution
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const bool FULL_SCREEN = false;
#else
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const bool FULL_SCREEN = true;
#endif
#endif

struct Vert
{
  Vert(Vec3 Position, Vec3 Color, Vec2 UVs);
  Vec3 position;
  Vec3 color;
  Vec2 uvs;
};

struct RenderObject
{
  RenderObject(int maxRenderSize /*In number of verticies*/);
  void ReAllocate(int newMaxRenderSize /*In number of verticies*/);
  void AddTriangle(Vert v1, Vert v2, Vert v3);
  void AddQuad(Vert v1, Vert v2, Vert v3, Vert v4);
  void SetTexture(char *bmpFile);
  void UploadToGPU();
  void Render();

private:

  unsigned int TextureID;

  float* PosData = nullptr;
  float* colData = nullptr;
  float* uvsData = nullptr;
  unsigned int posDataGLPtr = 0;
  unsigned int colDataGLPtr = 0;
  unsigned int uvsDataGLPtr = 0;
  unsigned int vertexCount = 0;
  unsigned int maxVertexCount = 0;
  unsigned int texture = -1;
};



bool Renderer_Initialise(); //Start SDL & Create Window
void Renderer_Destroy();
void Renderer_Render();
void Renderer_Swap(); //Update screen

void Renderer_AddQuad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4, Vec2 uv1, Vec2 uv2, Vec2 uv3, Vec2 uv4);
void Renderer_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset = 0, int ypixoffset = 0);

unsigned int Renderer_LoadTexture(char *path);

void Renderer_SetTextureID(unsigned int texID);
void Renderer_GenBuffers();
void Renderer_CreateBuffers(int verts);
void Renderer_DestroyBuffers();
void Renderer_BindShiz();

#endif // Renderer_h__
