#ifndef Renderer_h__
#define Renderer_h__

#include "Math/Vector.h"
#include <glm.hpp>

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include "SDL_opengles2.h"

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

  void Resize(int newMaxRenderSize /*In number of verticies*/);

  void SetTexture(GLuint TextureID);

  bool AddQuad(Vec3 pos1);

  GLfloat* PosData = nullptr;
  GLfloat* colData = nullptr;
  GLfloat* uvsData = nullptr;
  GLuint posDataGLPtr = 0;
  GLuint colDataGLPtr = 0;
  GLuint uvsDataGLPtr = 0;
  GLuint vertexCount = 0;
  GLuint maxVertexCount = 0;
  GLuint texture = -1;
};

bool Renderer_Initialise(); //Start SDL & Create Window
void Renderer_Destroy();
void Renderer_Render();
void Renderer_Swap(); //Update screen

void Renderer_AddQuad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4, Vec2 uv1, Vec2 uv2, Vec2 uv3, Vec2 uv4);
void Renderer_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset = 0, int ypixoffset = 0);

GLuint Renderer_LoadTexture(char *path);

void Renderer_SetTextureID(GLuint texID);
void Renderer_GenBuffers();
void Renderer_CreateBuffers(int verts);
void Renderer_DestroyBuffers();
void Renderer_BindShiz();

#endif // Renderer_h__
