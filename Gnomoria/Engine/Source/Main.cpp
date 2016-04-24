#pragma region Build Options

#define GLEW_STATIC

#pragma endregion

#pragma region includes

#include <stdio.h>
#include <string>
#include <tchar.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "SDL.h"
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include "SDL_opengles2.h"

#include "SDL_thread.h"

#include "Shaders.h"
#include "Camera.h"
#include <time.h>

#pragma endregion

#pragma region globals

//Program name
const char* PROGRAM_NAME = "Renderer";

//#define testWindow

#ifdef _DEBUG
//Window resolution
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const bool FULL_SCEEN = false;
#else
#ifdef testWindow
//Window resolution
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const bool FULL_SCEEN = false;
#else
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const bool FULL_SCEEN = true;
#endif
#endif

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Graphics program
GLuint gProgramID = 0;

//Uniform Locations
GLuint gLocMVP = -1;

GLuint gLocCAM = -1;

GLint gLocVertexPos4D = -1;
GLuint gLocTexture = -1;

#pragma endregion

#pragma region prototypes

bool init();

bool initGL();

void render();

void close();

uint32_t SafeGetBlock(uint8_t* world, int w, int h, int l, int x, int y, int z);

void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);

#pragma endregion


GLuint vertPosDataGLPtr = 0;
GLuint colPosDataGLPtr = 0;
GLuint UVPosDataGLPtr = 0;
GLfloat* vertPosData = nullptr;
GLfloat* colPosData = nullptr;
GLfloat* UVPosData = nullptr;
GLuint VertexCount = 0;
GLuint TextureID;

uint8_t *world;
int worldWidth = 1;
int worldHeight = 1;
int worldLength = 1;



//Occlusion Solving
glm::vec3 Solve(uint8_t* world, int w, int h, int l, int x, int z)
{
  int y = 0;
  x += h;
  y += h;
  z += h;

  while (((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l)))
  {
    x--; y--; z--;
  }

  while (true)
  {
    if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
      return glm::vec3(-1, -1, -1);
    uint8_t block = world[x + y*w + z * h * l];
    if (block > 0)
      return glm::vec3(x, y, z);
    x--; y--; z--;
  }

}

bool BlockIsExposed(uint8_t* world, int w, int h, int l, int x, int y, int z)
{
  while (true)
  {
    x++; y++; z++;
    if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
      return true;
    if (world[x + y*w + z * h * l] > 0)
      return false;
  }
}



//Gnomoria Rendering
void AddQuad_(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, glm::vec2 uv4)
{
}

void AddQuad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, glm::vec2 uv4)
{
  // Poly 1
  vertPosData[VertexCount * 3 + 0] = p1.x;
  vertPosData[VertexCount * 3 + 1] = p1.y;
  vertPosData[VertexCount * 3 + 2] = p1.z;
  colPosData[VertexCount * 3 + 0] = c1.x;
  colPosData[VertexCount * 3 + 1] = c1.y;
  colPosData[VertexCount * 3 + 2] = c1.z;
  UVPosData[VertexCount * 2 + 0] = uv1.x;
  UVPosData[VertexCount * 2 + 1] = uv1.y;
  VertexCount++;

  vertPosData[VertexCount * 3 + 0] = p2.x;
  vertPosData[VertexCount * 3 + 1] = p2.y;
  vertPosData[VertexCount * 3 + 2] = p2.z;
  colPosData[VertexCount * 3 + 0] = c2.x;
  colPosData[VertexCount * 3 + 1] = c2.y;
  colPosData[VertexCount * 3 + 2] = c2.z;
  UVPosData[VertexCount * 2 + 0] = uv2.x;
  UVPosData[VertexCount * 2 + 1] = uv2.y;
  VertexCount++;

  vertPosData[VertexCount * 3 + 0] = p4.x;
  vertPosData[VertexCount * 3 + 1] = p4.y;
  vertPosData[VertexCount * 3 + 2] = p4.z;
  colPosData[VertexCount * 3 + 0] = c4.x;
  colPosData[VertexCount * 3 + 1] = c4.y;
  colPosData[VertexCount * 3 + 2] = c4.z;
  UVPosData[VertexCount * 2 + 0] = uv4.x;
  UVPosData[VertexCount * 2 + 1] = uv4.y;
  VertexCount++;

  // Poly 2
  vertPosData[VertexCount * 3 + 0] = p2.x;
  vertPosData[VertexCount * 3 + 1] = p2.y;
  vertPosData[VertexCount * 3 + 2] = p2.z;
  colPosData[VertexCount * 3 + 0] = c2.x;
  colPosData[VertexCount * 3 + 1] = c2.y;
  colPosData[VertexCount * 3 + 2] = c2.z;
  UVPosData[VertexCount * 2 + 0] = uv2.x;
  UVPosData[VertexCount * 2 + 1] = uv2.y;
  VertexCount++;

  vertPosData[VertexCount * 3 + 0] = p3.x;
  vertPosData[VertexCount * 3 + 1] = p3.y;
  vertPosData[VertexCount * 3 + 2] = p3.z;
  colPosData[VertexCount * 3 + 0] = c3.x;
  colPosData[VertexCount * 3 + 1] = c3.y;
  colPosData[VertexCount * 3 + 2] = c3.z;
  UVPosData[VertexCount * 2 + 0] = uv3.x;
  UVPosData[VertexCount * 2 + 1] = uv3.y;
  VertexCount++;

  vertPosData[VertexCount * 3 + 0] = p4.x;
  vertPosData[VertexCount * 3 + 1] = p4.y;
  vertPosData[VertexCount * 3 + 2] = p4.z;
  colPosData[VertexCount * 3 + 0] = c4.x;
  colPosData[VertexCount * 3 + 1] = c4.y;
  colPosData[VertexCount * 3 + 2] = c4.z;
  UVPosData[VertexCount * 2 + 0] = uv4.x;
  UVPosData[VertexCount * 2 + 1] = uv4.y;
  VertexCount++;
}

bool TexelExists(uint8_t* img, int w, int h, int x, int y)
{
  if ((x < 0) | (y < 0) | (x >= w) | (y >= h))
    return false;
  uint8_t r = img[(x + y * w) * 3 + 2];
  uint8_t g = img[(x + y * w) * 3 + 1];
  uint8_t b = img[(x + y * w) * 3 + 0];
  uint8_t a = 255;
  if (r + g + b == 255 * 3)
    return false;
  return true;
}

GLuint LoadTexture(char * path)
{
  SDL_Surface *tex;
  GLuint texID = -1;
  if (tex = SDL_LoadBMP(path))
  {
    glGenTextures(1, &texID);
    //Turn white pixels transparent and upload texture to GL
    int w = tex->w;
    int h = tex->h;
    uint8_t *img = new uint8_t[w * h * 4];
    uint8_t* pixels = (uint8_t*)tex->pixels;
    for (int y = 0; y < h; y++)
    {
      for (int x = 0; x < w; x++)
      {
        uint8_t r = pixels[(x + y * w) * 3 + 2];
        uint8_t g = pixels[(x + y * w) * 3 + 1];
        uint8_t b = pixels[(x + y * w) * 3 + 0];
        uint8_t a = 255;

        if (r + g + b == 255 * 3)
        {
          //Transparent
          a = 0;
          //Find neighbor and use color
          int fixRadius = 8;
          //for (int ny = -1; ny <= 1; ny++)
          for (int ny = -fixRadius; ny <= fixRadius; ny++)
          {
            //for (int nx = -1; nx <= 1; nx++)
            for (int nx = -fixRadius; nx <= fixRadius; nx++)
            {
              if (TexelExists(pixels, w, h, x + nx, y + ny))
              {
                r = pixels[(x + nx + (y + ny) * w) * 3 + 2];
                g = pixels[(x + nx + (y + ny) * w) * 3 + 1];
                b = pixels[(x + nx + (y + ny) * w) * 3 + 0];
                break;
              }
            }
          }

        }

        img[(x + y * w) * 4 + 0] = r;
        img[(x + y * w) * 4 + 1] = g;
        img[(x + y * w) * 4 + 2] = b;
        img[(x + y * w) * 4 + 3] = a;

      }
    }

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(tex);
    delete[] img;
  }
  return texID;
}

void BuildMesh()
{
  VertexCount = 0;
  int verts = 0;
  //Make a graphical representation
  for (int y = 0; y < worldHeight; y++)
  {
    for (int x = 0; x < worldWidth; x++)
    {
      for (int z = 0; z < worldLength; z++)
      {
        float block = world[x + y*worldWidth + z * worldHeight * worldWidth];
        if (block > 0)
        {
          float b = y / 80.0f;
          if ( //basic wall solve
            (SafeGetBlock(world, worldWidth, worldHeight, worldLength, x + 1, y, z) == 0 &&
              BlockIsExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
            (SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y, z + 1) == 0 &&
              BlockIsExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
            //Wall
            verts += 6;
          if ( //basic floor solve
            SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y + 1, z) == 0 &&
            BlockIsExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
            //Floor
            verts += 6;
        }
      }
    }
  }

  delete[] vertPosData;
  delete[] UVPosData;
  delete[] colPosData;

  //Just enough Memory
  vertPosData = new GLfloat[verts * 3];
  colPosData = new GLfloat[verts * 3];
  UVPosData = new GLfloat[verts * 2];

  //Atleast Emough memory
  //vertPosData = new GLfloat[worldWidth * worldHeight * worldLength * 6 * 3 * 2];
  //UVPosData = new GLfloat[worldWidth * worldHeight * worldLength * 6 * 2 * 2];
  //colPosData = new GLfloat[worldWidth * worldHeight * worldLength * 6 * 3 * 2];

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
        float block = world[x + y*worldWidth + z * worldHeight * worldWidth];
        if (block > 0)
        {
          float b = y / 80.0f;
          if ( //basic wall solve
            (SafeGetBlock(world, worldWidth, worldHeight, worldLength, x + 1, y, z) == 0 &&
              BlockIsExposed(world, worldWidth, worldHeight, worldLength, x + 1, y, z)) ||
            (SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y, z + 1) == 0 &&
              BlockIsExposed(world, worldWidth, worldHeight, worldLength, x, y, z + 1))
            )
          {
            //Wall
            AddQuad(
              // Position
              glm::vec3(isoX, isoY, isoZ / 2.0),
              glm::vec3(isoX + 2, isoY, isoZ / 2.0),
              glm::vec3(isoX + 2, isoY, isoZ / 2.0 + 2),
              glm::vec3(isoX, isoY, isoZ / 2.0 + 2),
              // Color
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              // UV
              glm::vec2((block - 1) / 8.0, 1.0 / 16.0),
              glm::vec2((block + 1 - 1) / 8.0, 1.0 / 16.0),
              glm::vec2((block + 1 - 1) / 8.0, 1.0 / 8.0 + 1.0 / 16.0),
              glm::vec2((block - 1) / 8.0, 1.0 / 8.0 + 1.0 / 16.0)
              );
          }

          if ( //basic floor solve
            SafeGetBlock(world, worldWidth, worldHeight, worldLength, x, y + 1, z) == 0 &&
            BlockIsExposed(world, worldWidth, worldHeight, worldLength, x, y, z)
            )
          {
            //Floor
            AddQuad(
              // Position
              glm::vec3(isoX, isoY, isoZ / 2.0),
              glm::vec3(isoX + 2, isoY, isoZ / 2.0),
              glm::vec3(isoX + 2, isoY, isoZ / 2.0 + 1),
              glm::vec3(isoX, isoY, isoZ / 2.0 + 1),
              // Color
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              glm::vec3(b, b, b),
              // UV
              glm::vec2((block - 1) / 8.0, 0.0),
              glm::vec2((block + 1 - 1) / 8.0, 0.0),
              glm::vec2((block + 1 - 1) / 8.0, 1.0 / 16.0),
              glm::vec2((block - 1) / 8.0, 1.0 / 16.0)
              );
          }

        }
      }
    }
  }

  printf("%d verts\n", VertexCount);

  glGenBuffers(1, &vertPosDataGLPtr);
  glBindBuffer(GL_ARRAY_BUFFER, vertPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 3 * sizeof(GLfloat), vertPosData, GL_STATIC_DRAW);

  glGenBuffers(1, &UVPosDataGLPtr);
  glBindBuffer(GL_ARRAY_BUFFER, UVPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 2 * sizeof(GLfloat), UVPosData, GL_STATIC_DRAW);

  glGenBuffers(1, &colPosDataGLPtr);
  glBindBuffer(GL_ARRAY_BUFFER, colPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 3 * sizeof(GLfloat), colPosData, GL_STATIC_DRAW);
}



//Game World
uint8_t* LoadFromSchematic(char* MapPath, int &width, int &height, int &depth)
{
  FILE* inFile;
  if (fopen_s(&inFile, MapPath, "rb") != 0)
    return false;
  uint32_t fileLength;
  fseek(inFile, 0, SEEK_END);
  fileLength = ftell(inFile);
  fseek(inFile, 0, SEEK_SET);
  char* schematic = new char[fileLength];
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

  uint8_t *world = new uint8_t[width * height * depth];

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
                      case 2: blockid = 2 + (rand() & 1); break;
                      case 3: blockid = 4; break;
                      case 4: blockid = 0; break;
                      case 5: blockid = 0; break;
                      case 6: blockid = 0; break;
                      case 7: blockid = 1; break;
                      case 8: blockid = 5; break;
                      case 9: blockid = 5; break;
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

uint32_t SafeGetBlock(uint8_t* world, int w, int h, int l, int x, int y, int z)
{
  if ((x < 0) | (y < 0) | (z < 0) | (x >= w) | (y >= h) | (z >= l))
    return 0;
  return world[x + y*w + z * h * l];
}

void LoadWorld()
{
  TextureID = LoadTexture("Assets\\Textures\\Texture.bmp");
  world = LoadFromSchematic("Assets\\schematics\\small.schematic", worldWidth, worldHeight, worldLength);
  BuildMesh();
}



//Space Transforms
glm::vec2 ScreenToDevice(glm::vec2 ScreenPos)
{
  return (glm::vec2(ScreenPos.x / (SCREEN_WIDTH + 0.0), ScreenPos.y / (SCREEN_HEIGHT + 0.0)));
}

glm::vec2 DeviceToIso(glm::vec2 mousePos)
{
  float x = mousePos.x * 2 - 1;
  float y = mousePos.y * 2 - 1;
  x = camPos.x + x * camPos.y * (SCREEN_WIDTH + 0.0f) / SCREEN_HEIGHT;
  y = camPos.z + y * camPos.y;
  return glm::vec2(x, y * 2);
}

glm::vec2 IsoToOrtho(glm::vec2 IsoPos)
{
  glm::vec2 &i = IsoPos;
  i -= glm::vec2(1, 2);
  glm::vec2 OrthoPos((i.y + i.x) / 2, (i.y + i.x) / 2 - i.x);
  return OrthoPos;
}

glm::ivec3 ScreenToWorld(glm::vec2 ScreenPos)
{
  glm::vec2 DeviceSpace = ScreenToDevice(ScreenPos);
  glm::vec2 IsoSpace = DeviceToIso(DeviceSpace);
  glm::vec2 OrthoSpace = IsoToOrtho(IsoSpace);
  return Solve(world, worldWidth, worldHeight, worldLength, (int)OrthoSpace.x, (int)OrthoSpace.y);
}



//OpenGL
bool init()
{
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Error: SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //Use OpenGL 3.1 core
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  //Enable AA
  //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  //Create window
  gWindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | (SDL_WINDOW_FULLSCREEN * FULL_SCEEN));
  if (gWindow == NULL)
  {
    printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetWindowBordered(gWindow, SDL_FALSE);


  //Create context
  gContext = SDL_GL_CreateContext(gWindow);
  if (gContext == NULL)
  {
    printf("Error: OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //Initialize GLEW
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK)
  {
    printf("Error: Unable to initialize GLEW! %s\n", glewGetErrorString(glewError));
    return false;
  }

  //Enable Vsync
  if (SDL_GL_SetSwapInterval(1) < 0)
  {
    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
  }

  //Initialize OpenGL
  if (!initGL())
  {
    printf("Error: Unable to initialize OpenGL!\n");
    return false;
  }

  //Successful init
  return true;
}

bool initGL()
{
  //Depth Testing
  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  //Multi sampling
  //glEnable(GL_MULTISAMPLE);

  //Generate shader program
  gProgramID = glCreateProgram();

  //Create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  //Get vertex source
  char *vertShader[1];
  vertShader[0] = LoadShader("assets\\Shaders\\Vert\\texture.vert");

  //Set vertex source
  glShaderSource(vertexShader, 1, vertShader, NULL);

  //Compile vertex source
  glCompileShader(vertexShader);

  //Check vertex shader for errors
  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
  if (vShaderCompiled != GL_TRUE)
  {
    printf("Unable to compile vertex shader %d!\n", vertexShader);
    printShaderLog(vertexShader);
    return false;
  }

  //Attach vertex shader to program
  glAttachShader(gProgramID, vertexShader);

  //Create fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  //Get fragment source
  char *fragShader[1];

  fragShader[0] = LoadShader("assets\\Shaders\\frag\\texture.frag");

  //Set fragment source
  glShaderSource(fragmentShader, 1, fragShader, NULL);

  //Compile fragment source
  glCompileShader(fragmentShader);

  //Check fragment shader for errors
  GLint fShaderCompiled = GL_FALSE;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
  if (fShaderCompiled != GL_TRUE)
  {
    printf("Unable to compile fragment shader %d!\n", fragmentShader);
    printShaderLog(fragmentShader);
    return false;
  }

  //Attach fragment shader to program
  glAttachShader(gProgramID, fragmentShader);

  //Link program
  glLinkProgram(gProgramID);

  //Check for errors
  GLint programSuccess = GL_TRUE;
  glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
  if (programSuccess != GL_TRUE)
  {
    printf("Error linking program %d!\n", gProgramID);
    printProgramLog(gProgramID);
    return false;
  }

  //Get vertex attribute locations
  gLocVertexPos4D = glGetAttribLocation(gProgramID, "vert");
  if (gLocVertexPos4D == -1)
  {
    printf("vert is not a valid glsl program variable!\n");
    return false;
  }

  //Model View Projection Shader parameter
  gLocMVP = glGetUniformLocation(gProgramID, "MVP");
  gLocCAM = glGetUniformLocation(gProgramID, "CAM");

  gLocTexture = glGetUniformLocation(gProgramID, "TextureSampler");

  //Initialize clear color
  glClearColor(0.f, 0.0, 0.0, 1.f);

  //success
  return true;
}

void render()
{
  //Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Bind shader program
  glUseProgram(gProgramID);

  // Projection matrix (Field of View, Aspect Ratio, NearPlane, FarPlane)
  glm::mat4 Projection = glm::perspective(45.0f, (SCREEN_WIDTH + 0.0f) / SCREEN_HEIGHT, 0.1f, 10000.0f);

  // Camera matrix
  glm::mat4 View;

  // Model Matrix
  glm::mat4 Model = glm::mat4(1.0f);

  static float rot = 0.0;
  rot = rot - 0.00333f;

  // Model View Projection Matrix
  glm::mat4 MVP = Projection * View * Model;

  //Bind Vert Shader Attributes
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  //Reset camera and depth buffer
  glClear(GL_DEPTH_BUFFER_BIT);
  View = getCamera();
  Model = glm::mat4(1.0f);
  MVP = Projection * View * Model;

  glUniformMatrix4fv(gLocMVP, 1, GL_FALSE, &MVP[0][0]);

  glm::vec4 ShaderCam(camPos, (SCREEN_HEIGHT*1.0f) / SCREEN_WIDTH);
  glUniform4fv(gLocCAM, 1, (GLfloat*)&ShaderCam);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //vertex positions
  glBindBuffer(GL_ARRAY_BUFFER, vertPosDataGLPtr);
  glVertexAttribPointer
    (
      0,                  // attribute number. must match the layout in the shader.
      3,                  // count
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );


  //texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, UVPosDataGLPtr);
  glVertexAttribPointer(
    1,                  // attribute number. must match the layout in the shader.
    2,                  // count
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

  //texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, colPosDataGLPtr);
  glVertexAttribPointer(
    2,                  // attribute number. must match the layout in the shader.
    3,                  // count
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

  glBindTexture(GL_TEXTURE_2D, TextureID);

  glDrawArrays(GL_TRIANGLES, 0, VertexCount);

  //Unbind Vert Shader Attributes
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  //Unbind program
  glUseProgram(NULL);

}

void close()
{
  //Deallocate program
  glDeleteProgram(gProgramID);

  //Destroy window	
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  //Quit SDL
  SDL_Quit();
}

void printProgramLog(GLuint program)
{
  //Make sure name is shader
  if (glIsProgram(program))
  {
    //Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
      //Print Log
      printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
  }
  else
  {
    printf("Name %d is not a program\n", program);
  }
}

void printShaderLog(GLuint shader)
{
  //Make sure name is shader
  if (glIsShader(shader))
  {
    //Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
      //Print Log
      printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
  }
  else
  {
    printf("Name %d is not a shader\n", shader);
  }
}



//Main Loop
int wmain(int argc, char* argv[])
{

  //Start SDL & Create Window
  if (!init())
  {
    printf("Failed to initialize!\n");
    getchar();
    return 1;
  }

  LoadWorld();

  //Take control of the cursor
  //SDL_SetRelativeMouseMode(SDL_TRUE);

  //Main loop flag
  bool running = true;

  //Event handler
  SDL_Event e;

  //Enable text input
  //SDL_StartTextInput();

  while (running)
  {
    //Handle SDL queue
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT) // User closed window?
        running = false;
      if (e.type == SDL_KEYDOWN) // User pressed esc?
        if (e.key.keysym.sym == SDLK_ESCAPE)
          running = false;

      // mouse was moved
      int x = 0, y = 0;
      if (e.type == SDL_MOUSEMOTION)
      {
        //x = e.motion.xrel;
        //y = e.motion.yrel;
        //MouseControls(x, y);
      }


      int xmouse;
      int ymouse;
      if (SDL_GetMouseState(&xmouse, &ymouse) & SDL_BUTTON(SDL_BUTTON_LEFT))
      {
        glm::ivec3 pos = ScreenToWorld(glm::vec2(xmouse, ymouse));
        world[pos.x + pos.y * worldWidth + pos.z * worldWidth*worldHeight] = 0;
        BuildMesh();
      }

      if (SDL_GetMouseState(&xmouse, &ymouse) & SDL_BUTTON(SDL_BUTTON_RIGHT))
      {
        glm::ivec3 pos = ScreenToWorld(glm::vec2(xmouse, ymouse));
        world[pos.x + (pos.y + 1) * worldWidth + pos.z * worldWidth*worldHeight] = 1;
        BuildMesh();
      }


    }

    //Handle keyboard input
    const static unsigned char *keyboard = SDL_GetKeyboardState(NULL);
    glm::vec3 camOff;

    {//3d movement
      camOff = CameraKeyboardControls(keyboard);
      camPos += camOff;

      if (camPos.y > 80)
        camPos.y = 80;

      if (camPos.y < 8)
        camPos.y = 8;

    }

    //Render
    render();

    static int lastFrame = 0;
    static int frames = 0;
    frames++;
    if (clock() - lastFrame > 1000)
    {
      printf("%d\n\n", frames);
      frames = 0;
      lastFrame = clock();
    }

    //Update screen
    SDL_GL_SwapWindow(gWindow);

    //Just in case Vsync fails!
    //Sleep(15);

  }

  //Free engine resources
  close();

  return 0; // return success!
}
