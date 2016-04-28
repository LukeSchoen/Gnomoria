#include "World.h"
#include "Renderer.h"
#include "Camera.h"

#include "SDL.h"

uint8_t *world;
int worldWidth = 1;
int worldHeight = 1;
int worldLength = 1;

glm::vec3 World_Solve(uint8_t *world, int w, int h, int l, int x, int z)
{
  int y = 0;
  x += h;
  y += h;
  z += h;

  int giveup = 0;
  while (((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l)))
  {
    x--; y--; z--;
    giveup++;
    if (giveup > 1024)
    {
      return glm::vec3(-1, -1, -1);
    }
  }

  while (true)
  {
    if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
      return glm::vec3(-1, -1, -1);
    uint8_t block = world[x + y*w + z *h *l];
    if (block > 0)
      return glm::vec3(x, y, z);
    x--; y--; z--;
  }
}

uint8_t * World_LoadFromSchematic(char *MapPath, int &width, int &height, int &depth)
{
  FILE *inFile;
  if (fopen_s(&inFile, MapPath, "rb") != 0)
    return false;
  uint32_t fileLength;
  fseek(inFile, 0, SEEK_END);
  fileLength = ftell(inFile);
  fseek(inFile, 0, SEEK_SET);
  char *schematic = new char[fileLength];
  fread(schematic, 1, fileLength, inFile);
  fclose(inFile);
  uint32_t i = 0;

  while (i < fileLength)
  {

    if (schematic[i++] == 'H')
    {
      if (schematic[i++] == 'e')
      {
        if (schematic[i++] == 'i')
        {
          if (schematic[i++] == 'g')
          {
            if (schematic[i++] == 'h')
            {
              if (schematic[i++] == 't')
              {
                uint32_t temp = (uint8_t)schematic[i++];
                uint32_t temp2 = (uint8_t)schematic[i++];
                height = ((temp << 8) + temp2);
                break;
              }
            }
          }
        }
      }
    }
  }
  while (i < fileLength)
  {

    if (schematic[i++] == 'L')
    {
      if (schematic[i++] == 'e')
      {
        if (schematic[i++] == 'n')
        {
          if (schematic[i++] == 'g')
          {
            if (schematic[i++] == 't')
            {
              if (schematic[i++] == 'h')
              {
                uint32_t temp = (uint8_t)schematic[i++];
                uint32_t temp2 = (uint8_t)schematic[i++];
                depth = ((temp << 8) + temp2);
                break;
              }
            }
          }
        }
      }
    }
  }
  while (i < fileLength)
  {

    if (schematic[i++] == 'W')
    {
      if (schematic[i++] == 'i')
      {
        if (schematic[i++] == 'd')
        {
          if (schematic[i++] == 't')
          {
            if (schematic[i++] == 'h')
            {
              uint32_t temp = (uint8_t)schematic[i++];
              uint32_t temp2 = (uint8_t)schematic[i++];
              width = ((temp << 8) + temp2);
              break;
            }
          }
        }
      }
    }
  }

  uint8_t *world = new uint8_t[width *height *depth];

  int blockid;
  while (i < fileLength)
  {

    if (schematic[i++] == 'B')
    {
      if (schematic[i++] == 'l')
      {
        if (schematic[i++] == 'o')
        {
          if (schematic[i++] == 'c')
          {
            if (schematic[i++] == 'k')
            {
              if (schematic[i++] == 's')
              {
                i += 4;
                for (int y = 0; y < height; y++)
                {
                  for (int x = 0; x < width; x++)
                  {
                    for (int z = 0; z < depth; z++)
                    {
                      blockid = ((uint8_t*)schematic)[i++];

                      switch (blockid)
                      {
                      case 1: blockid = 1; break;
                      case 2: blockid = 4; break;
                      case 3: blockid = 2; break;
                      case 4: blockid = 0; break;
                        //case 5: blockid = 0; break;
                        //case 6: blockid = 0; break;
                        //case 7: blockid = 1; break;
                      case 8: blockid = 6; break;
                      case 9: blockid = 6; break;
                      case 12: blockid = 5; break;
                        //WOOD case 17: blockid = 7; break;
                      default: blockid = 0; break;
                      }

                      world[x + y*width + z*width*height] = blockid;
                    }
                  }
                }
                break;
              }
            }
          }
        }
      }
    }
  }
  delete[]schematic;
  return world;
}

void World_Update()
{
  int xmouse;
  int ymouse;
  if (SDL_GetMouseState(&xmouse, &ymouse) & SDL_BUTTON(SDL_BUTTON_LEFT))
  {
    glm::ivec3 pos = World_ScreenToWorld(glm::vec2(xmouse, ymouse));
    world[pos.x + pos.y *worldWidth + pos.z *worldWidth*worldHeight] = 0;
    World_BuildMesh();
  }

  if (SDL_GetMouseState(&xmouse, &ymouse) & SDL_BUTTON(SDL_BUTTON_RIGHT))
  {
    glm::ivec3 pos = World_ScreenToWorld(glm::vec2(xmouse, ymouse));
    world[pos.x + (pos.y + 1) *worldWidth + pos.z *worldWidth*worldHeight] = 1;
    World_BuildMesh();
  }
}

void World_LoadWorld()
{
  Renderer_SetTextureID(Renderer_LoadTexture("Assets\\Textures\\Texture.bmp"));
  world = World_LoadFromSchematic("Assets\\schematics\\small.schematic", worldWidth, worldHeight, worldLength);
  World_BuildMesh();
}

bool World_IsBlockExposed(uint8_t *world, int w, int h, int l, int x, int y, int z)
{
  while (true)
  {
    x++; y++; z++;
    if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
      return true;
    if (world[x + y*w + z *h *l] > 0)
      return false;
  }
}

uint32_t World_SafeGetBlock(uint8_t *world, int w, int h, int l, int x, int y, int z)
{
  if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
    return 0;
  return world[x + y*w + z *h *l];
}

void World_BuildMesh()
{
  int vertexCount = 0;
  int verts = 0;
  //Make a graphical representation
  for (int y = 0; y < worldHeight; y++)
  {
    for (int x = 0; x < worldWidth; x++)
    {
      for (int z = 0; z < worldLength; z++)
      {
        uint8_t block = world[x + y*worldWidth + z *worldHeight *worldWidth];
        if (block > 0)
        {
          float b = y / 80.0f;
          if ( //basic wall solve
            (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x + 1, y, z) == 0 &&
              World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
              (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y, z + 1) == 0 &&
                World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
            //Wall
            verts += 6;
          if ( //basic floor solve
            World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y + 1, z) == 0 &&
            World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
            //Floor
            verts += 6;
        }
      }
    }
  }

  Renderer_DestroyBuffers();
  Renderer_CreateBuffers(Vec3i(worldWidth, worldHeight, worldLength));

  //Make a graphical representation
  for (int y = 0; y < worldHeight; y++)
  {
    for (int x = 0; x < worldWidth; x++)
    {
      for (int z = 0; z < worldLength; z++)
      {
        int isoX = x - z;
        int isoY = y;
        int isoZ = x + z - y * 2;
        isoY = 0;
        uint8_t block = world[x + y*worldWidth + z *worldHeight *worldWidth];
        if (block > 0)
        {
          float b = y / 80.0f;
          bool drawn = false;
          if ( //basic wall solve
            (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x + 1, y, z) == 0 &&
              World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
              (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y, z + 1) == 0 &&
                World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
          {
            Renderer_AddTile(x, y, z, { b, b, b }, 32 + block);
            drawn = true;
          }

          if ( //basic floor solve
            World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y + 1, z) == 0 &&
            World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
          {
            Renderer_AddTile(x, y, z, { b, b, b }, 16 + block);
            drawn = true;
          }
          if (drawn)
          {
            if (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x - 1, y, z) == 0)
              Renderer_AddTile(x, y, z, { b, b, b }, 5, 0, -1);
            if (World_SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y, z - 1) == 0)
              Renderer_AddTile(x, y, z, { b, b, b }, 6, 0, -1);
          }

        }
      }
    }
  }

  printf("%d verts\n", vertexCount);
  Renderer_BindShiz(vertexCount);
}

//Space Transforms
glm::vec2 _ScreenToDevice(glm::vec2 ScreenPos)
{
  return (glm::vec2(ScreenPos.x / (SCREEN_WIDTH + 0.0), ScreenPos.y / (SCREEN_HEIGHT + 0.0)));
}

glm::vec2 _DeviceToIso(glm::vec2 mousePos)
{
  float x = mousePos.x * 2 - 1;
  float y = mousePos.y * 2 - 1;
  x = camPos.x + x *camPos.y *(SCREEN_WIDTH + 0.0f) / SCREEN_HEIGHT;
  y = camPos.z + y *camPos.y;
  return glm::vec2(x, y * 2);
}

glm::vec2 _IsoToOrtho(glm::vec2 IsoPos)
{
  glm::vec2 &i = IsoPos;
  i -= glm::vec2(1, 2);
  glm::vec2 OrthoPos((i.y + i.x) / 2, (i.y + i.x) / 2 - i.x);
  return OrthoPos;
}


glm::ivec3 World_ScreenToWorld(glm::vec2 ScreenPos)
{
  glm::vec2 DeviceSpace = _ScreenToDevice(ScreenPos);
  glm::vec2 IsoSpace = _DeviceToIso(DeviceSpace);
  glm::vec2 OrthoSpace = _IsoToOrtho(IsoSpace);
  return World_Solve(world, worldWidth, worldHeight, worldLength, (int)OrthoSpace.x, (int)OrthoSpace.y);
}