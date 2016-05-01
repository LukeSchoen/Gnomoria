#ifndef Renderer_h__
#define Renderer_h__

#include "Math/Vector.h"

const int USE_VSYNC = 1;

//#define testWindow

#ifdef _DEBUG
//Window resolution
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const bool FULL_SCREEN = false;
#else
#ifdef testWindow
//Window resolution
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const bool FULL_SCREEN = false;
#else
const int SCREEN_WIDTH = 1024;
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
  RenderObject(int maxRenderSize = 0);
  void ReAllocate(int newMaxRenderSize /*In number of verticies*/);
  void AddTriangle(Vert v1, Vert v2, Vert v3);
  void AddQuad(Vert v1, Vert v2, Vert v3, Vert v4);
  void Clear();
  void AssignTexture(char *bmpFile);
  void UploadToGPU();
  void Render();
  void Destroy();
private:
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


bool Renderer_Initialise(); //open SDL and Window
void Renderer_Destroy(); //close SDL and window
void Renderer_Swap(); //Update screen
void Renderer_Clear(); //clear screen

#endif // Renderer_h__
