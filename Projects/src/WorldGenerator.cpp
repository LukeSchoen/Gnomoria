#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <direct.h>
#include "Chunk.h"
#include "WorldPaths.h"
#include "File.h"
#include "GString.h"
#include "Image.h"
#include "WorldGenerator.h"
#include "Math/GMMath.h"
#include "PerlinNoise.h"
#include "AdvNoise.h"

//Creating new world projects
static Chunk blankChunk;
void CreateChunk(Vec3i chunkPos, char* chunkDataPath)
{
  char* chunkFile = WorldChunkName(chunkPos, chunkDataPath);
  WriteFile(chunkFile, blankChunk.Data, Chunk::dataSize);
}
void WorldGenerator::Create(char* worldName, Vec3i worldSize)
{
  delete[] worldFilePath;
  worldFilePath = strcpy(worldName);

  //Create world directories
  Loaded = true;
  mkdir(WorldMainPath(worldName));
  mkdir(WorldChunksPath(worldName));

  //Save World Dimensions
  WriteFile(WorldSizePath(worldName), &worldSize, sizeof(worldSize));

  int chunkWidth = ceil((worldSize.x + 0.0) / Chunk::width);
  int chunkHeight = ceil((worldSize.y + 0.0) / Chunk::height);
  int chunkLength = ceil((worldSize.z + 0.0) / Chunk::length);

  for (int y = 0; y < chunkHeight; y++)
  {
    for (int z = 0; z < chunkLength; z++)
    {
      for (int x = 0; x < chunkWidth; x++)
      {
        CreateChunk(Vec3i(x, y, z), WorldChunksPath(worldName));
      }
    }
  }

}

WorldGenerator *WorldGenerator::GetInstance()
{
  static WorldGenerator *instance;
  if (!instance)
  {
    instance = new WorldGenerator();
    Block emptyBlock;
    emptyBlock.floorType = 0;
    for (int i = 0; i < blankChunk.dataSize; i++)
      blankChunk.Data[i] = emptyBlock;
  }
  return instance;
}






NoiseMap TaperBorders(NoiseMap source, int borderDistance)
{
  NoiseMap ret(source.size);
  for (int z = 0; z < source.size.y; z++)
  {
    for (int x = 0; x < source.size.x; x++)
    {
      float height = source.GetValue(Vec2i(x, z));

      //Map Edge tapper off
      float edge = x;
      edge = min(edge, z);
      edge = min(edge, source.size.x - x);
      edge = min(edge, source.size.y - z);
      if (edge < borderDistance)
      {
        edge = 1.0 - (edge / borderDistance);
        height -= edge;
        height = max(height, 0);
        ret.SetValue(Vec2i(x, z), height);
      }
      else
      {
        ret.SetValue(Vec2i(x, z), height);
      }
    }
  }
  return ret;
}

void WorldGenerator::GenerateWorld()
{
  WorldAccess &gameWorld = *WorldAccess::GetInstance();
  PerlinNoiseGenerator worldNoiseGenerator;
  
  //Get the worlds dimensions
  Vec3i worldSize = gameWorld.GetSize();
  
  //Generate Perlin Noise
  NoiseMap worldNoise = worldNoiseGenerator.GeneratePerlinNoise(worldSize.x, worldSize.z, 7);

  //Add Perlin turbulence
  worldNoise = AdvNoise::SampleWithTurbulance(worldNoise, 7, 255);

  //Lower too sea level around map border
  worldNoise = TaperBorders(worldNoise, 64);

  //Place Blocks into world
  for (int z = 0; z < worldSize.z; z++)
  {
    for (int x = 0; x < worldSize.x; x++)
    {
      float height = worldNoise.GetValue(Vec2i(x, z));

      Vec3i pos(x, 0, z);
      Block block;

      if (height > 54 / 255.0)
        block.floorType = 2;
      else
        block.floorType = 9;

      gameWorld.SetBlock(pos, block);

    }
  }

}

//For Testing
void testworldgen()
{
  int mapSize = 1024;

  PerlinNoiseGenerator worldNoiseGenerator;
  Vec3i worldSize(mapSize, 256, mapSize);


  for (int image = 0; image < 256; image++)
  {
    int turbulance = image * 32;

    //Generate Perlin Noise
    NoiseMap worldNoise = worldNoiseGenerator.GeneratePerlinNoise(worldSize.x + turbulance, worldSize.z + turbulance, 7);

    //Add Perlin turbulence
    worldNoise = AdvNoise::SampleWithTurbulance(worldNoise, 7, turbulance);

    //Lower too sea level around map border
    worldNoise = TaperBorders(worldNoise, 64);

    Image output(mapSize, mapSize);

    //Place Blocks into world
    for (int z = 0; z < worldSize.z; z++)
    {
      for (int x = 0; x < worldSize.x; x++)
      {
        float height = worldNoise.GetValue(Vec2i(x, z));

        int nheight = height * 255;

        int waterHeight = 148;
        int beachHeight = 16;
        int grassHeight = 48;
        int treesHeight = 256;

        int threshold = waterHeight;
        if (nheight < threshold)
        {
          output.SetPixel(x, z, 255 + 64 * 256 + 0 * 256 * 256); continue;
        }

        threshold += beachHeight;
        if (nheight < threshold)
        {
          output.SetPixel(x, z, 128 + 220 * 256 + 255 * 256 * 256); continue;
        }

        threshold += grassHeight;
        if (nheight < threshold)
        {
          output.SetPixel(x, z, 32 + 190 * 256 + 24 * 256 * 256); continue;
        }

        threshold += treesHeight;
        if (nheight < threshold)
        {
          output.SetPixel(x, z, 9 + 64 * 256 + 3 * 256 * 256); continue;
        }



        //if (nheight > 148)
          output.SetPixel(x, z, nheight + nheight * 256 + nheight * 256 * 256);
        //else
          //output.SetPixel(x, z, 123 + 76 * 256);
      }
    }
    char imageName[256];
    sprintf(imageName, "C:/Users/Administrator/Desktop/Gnomoria/heightMap%d.bmp", image);
    output.Save(imageName);
  }
  system("C:/Users/Administrator/Desktop/Gnomoria/heightMap.bmp");
  exit(0);
}


