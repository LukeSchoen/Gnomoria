#include "World.h"
#include "Renderer.h"

uint8_t *world;
int worldWidth = 1;
int worldHeight = 1;
int worldLength = 1;

RenderObject *worldMesh = nullptr;

Vec3i World_Solve(int x, int z)
{
  int y = 0;
  x += worldHeight;
  y += worldHeight;
  z += worldHeight;

  int giveup = 0;
  while (((x < 0) | (y < 0) | (z < 0) | (x >= worldWidth) | (y >= worldHeight) | (z >= worldLength)))
  {
    x--; y--; z--;
    giveup++;
    if (giveup > 1024)
    {
      return Vec3i(-1, -1, -1);
    }
  }

  while (true)
  {
    if ((x < 0) | (y < 0) | (z < 0) | (x >= worldWidth) | (y >= worldHeight) | (z >= worldLength))
      return Vec3i(-1, -1, -1);
    uint8_t block = world[x + y * worldWidth + z * worldHeight * worldLength];
    if (block > 0)
      return Vec3i(x, y, z);
    x--; y--; z--;
  }
}

uint32_t World_GetBlock(Vec3i pos)
{
  if ((pos.x < 0) | (pos.y < 0) | (pos.z < 0) | (pos.x >= worldWidth) | (pos.y >= worldHeight) | (pos.z >= worldLength))
    return 0;
  return world[pos.x + pos.y * worldWidth + pos.z * worldHeight * worldLength];
}

void World_SetBlock(Vec3i pos, uint32_t blockID)
{
  if ((pos.x < 0) | (pos.y < 0) | (pos.z < 0) | (pos.x >= worldWidth) | (pos.y >= worldHeight) | (pos.z >= worldLength))
    return;
  world[pos.x + pos.y * worldWidth + pos.z * worldHeight * worldLength] = blockID;
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

void World_LoadWorld()
{
  world = World_LoadFromSchematic("Assets\\schematics\\small.schematic", worldWidth, worldHeight, worldLength);
  World_BuildMesh();
}




void World_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset /*= 0*/, int ypixoffset /*= 0*/)
{
  tex--;
  int isoX = posx - posz;
  int isoY = posy;
  int isoZ = posx + posz - posy * 2;
  isoY = 0;
  int AtlasTileWidth = 16;
  float iATW = 1.0f / AtlasTileWidth;
  int tx = tex % AtlasTileWidth;
  int ty = tex / AtlasTileWidth;
  float u = tx * iATW;
  float v = ty * iATW;

  float x = xpixoffset / 16.0f;
  float y = ypixoffset / 16.0f;

  worldMesh->AddQuad(
    Vert(
      Vec3(isoX + x, (float)isoY, isoZ / 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u, v)),
    Vert(
      Vec3(isoX + 2 + x, (float)isoY, isoZ / 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u + iATW, v)),
    Vert(
      Vec3(isoX + 2 + x, (float)isoY, isoZ / 2.0f + 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u + iATW, v + iATW)),
    Vert(
      Vec3(isoX + x, (float)isoY, isoZ / 2.0f + 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u, v + iATW))
    );
}

void World_BuildMesh()
{
  if (!worldMesh)
  {
    worldMesh = new RenderObject(0);
    worldMesh->AssignTexture("Assets\\Textures\\Texture.bmp");
  }

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
          bool drawn = false;
          if ( //basic wall solve
            (World_GetBlock(Vec3i(x + 1, y, z)) == 0 &&
              World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
              (World_GetBlock(Vec3i(x, y, z+1)) == 0 &&
                World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
            //Wall
          {
            verts += 6;
            drawn = true;
          }

          if ( //basic floor solve
            World_GetBlock(Vec3i(x, y + 1, z)) == 0 &&
            World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
            //Floor
          {
            verts += 6;
            drawn = true;
          }

          if (drawn)
          {
            if (World_GetBlock(Vec3i(x - 1, y, z)) == 0)
              verts += 6;
            if (World_GetBlock(Vec3i(x, y, z-1)) == 0)
              verts += 6;
          }
        }
      }
    }
  }

  worldMesh->ReAllocate(verts);
  worldMesh->Clear();

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
            (World_GetBlock(Vec3i(x + 1, y, z)) == 0 &&
              World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
            (World_GetBlock(Vec3i(x, y, z + 1)) == 0 &&
              World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
          {
            World_AddTile(x, y, z, { b, b, b }, 32 + block);
            drawn = true;
          }

          if ( //basic floor solve
            World_GetBlock(Vec3i(x, y + 1, z)) == 0 &&
            World_IsBlockExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
          {
            World_AddTile(x, y, z, { b, b, b }, 16 + block);
            drawn = true;
          }
          if (drawn)
          {
            if (World_GetBlock(Vec3i(x - 1, y, z)) == 0)
              World_AddTile(x, y, z, { b, b, b }, 5, 0, -1);
            if (World_GetBlock(Vec3i(x, y, z - 1)) == 0)
              World_AddTile(x, y, z, { b, b, b }, 6, 0, -1);
          }

        }
      }
    }
  }

  worldMesh->UploadToGPU();
}

void World_Draw()
{
  worldMesh->Render();
}