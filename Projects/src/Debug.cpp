#include "Debug.h"
#include "World.h"
#include "Renderer.h"

static bool Updated = false;
static int RenderSize = 0;
static int MaxRenderSize = 600;
static RenderObject *debugMesh = nullptr;

void _Initialize()
{
  if (!debugMesh)
  {
    debugMesh = new RenderObject(MaxRenderSize);
    debugMesh->AssignTexture("Assets\\Textures\\Texture.bmp");
  }
}

void _PrepareForGeometry()
{
  _Initialize();
  while ((RenderSize + 6) >= MaxRenderSize)
  {
    MaxRenderSize = MaxRenderSize * 2 + 1;
    debugMesh->ReAllocate(MaxRenderSize);
  }
  RenderSize += 6;
  Updated = false;
}

void Debug_Draw()
{
  _Initialize();
  if (!Updated)
  {
    Updated = true;
    debugMesh->UploadToGPU();
  }
  debugMesh->Render();
}

void Debug_Clear()
{
  debugMesh->Clear();
  RenderSize = 0;
}

void Debug_AddFloorLine(Vec3i pos, Vec3 col)
{
  _PrepareForGeometry();
  World_AddTile(debugMesh, pos.x, pos.y, pos.z, col, 1);
}

void Debug_AddFloorFill(Vec3i pos, Vec3 col)
{
  _PrepareForGeometry();
  World_AddTile(debugMesh, pos.x, pos.y, pos.z, col, 3);
}

void Debug_AddWallLine(Vec3i pos, Vec3 col)
{
  _PrepareForGeometry();
  World_AddTile(debugMesh, pos.x, pos.y, pos.z, col, 2);
}

void Debug_AddWallFill(Vec3i pos, Vec3 col)
{
  _PrepareForGeometry();
  World_AddTile(debugMesh, pos.x, pos.y, pos.z, col, 4);
}