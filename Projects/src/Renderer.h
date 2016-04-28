#ifndef Renderer_h__
#define Renderer_h__

#include <glm.hpp>
#include "Math/Vector.h"

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

bool Renderer_Initialise(); //Start SDL & Create Window
void Renderer_Destroy();
void Renderer_Render();
void Renderer_Swap(); //Update screen

void Renderer_AddQuad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4, Vec2 uv1, Vec2 uv2, Vec2 uv3, Vec2 uv4);
void Renderer_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset = 0, int ypixoffset = 0);

GLuint Renderer_LoadTexture(char *path);

void Renderer_SetTextureID(GLuint texID);
void Renderer_GenBuffers();
void Renderer_CreateBuffers(Vec3i worldSize);
void Renderer_DestroyBuffers();
void Renderer_BindShiz(int vertexCount);

#endif // Renderer_h__
