#pragma region Build Options

#define GLEW_STATIC

#pragma endregion

#pragma region includes

#include <stdio.h>
#include <string>
#include <tchar.h>

#include "SDL.h"
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include "SDL_opengles2.h"

#include "SDL_thread.h"

#include "Shaders.h"
#include "Camera.h"
#include <time.h>

#include "Renderer.h"

//Program name
const char* PROGRAM_NAME = "Gnomoria";

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Graphics program
GLuint gProgramID = 0;

//Uniform Locations
GLuint gLocCAM = -1;
GLint gLocVertexPos4D = -1;
GLuint gLocTextureSampler = -1;

//Overall Draw Count Recorder
static int PolyCount = 0;

bool _TexelExists(uint8_t *img, int w, int h, int x, int y);

Vert::Vert(Vec3 Position, Vec3 Color, Vec2 UVs)
{
  position = Position;
  color = Color;
  uvs = UVs;
};

RenderObject::RenderObject(int maxRenderSize)
{
  glGenBuffers(1, &posDataGLPtr);
  glGenBuffers(1, &colDataGLPtr);
  glGenBuffers(1, &uvsDataGLPtr);
  ReAllocate(maxRenderSize);
  vertexCount = 0;
}

void RenderObject::ReAllocate(int maxRenderSize)
{
  if (maxRenderSize > maxVertexCount)
  {
    PosData = (float*)realloc(PosData, sizeof(float) * maxRenderSize * 3);
    colData = (float*)realloc(colData, sizeof(float) * maxRenderSize * 3);
    uvsData = (float*)realloc(uvsData, sizeof(float) * maxRenderSize * 2);
    maxVertexCount = maxRenderSize;
  }
}

void RenderObject::AddTriangle(Vert v1, Vert v2, Vert v3)
{
  Vec3 &p1 = v1.position;
  Vec3 &p2 = v2.position;
  Vec3 &p3 = v3.position;

  Vec3 &c1 = v1.color;
  Vec3 &c2 = v2.color;
  Vec3 &c3 = v3.color;

  Vec2 &uv1 = v1.uvs;
  Vec2 &uv2 = v2.uvs;
  Vec2 &uv3 = v3.uvs;

  PosData[vertexCount * 3 + 0] = p1.x;
  PosData[vertexCount * 3 + 1] = p1.y;
  PosData[vertexCount * 3 + 2] = p1.z;
  colData[vertexCount * 3 + 0] = c1.x;
  colData[vertexCount * 3 + 1] = c1.y;
  colData[vertexCount * 3 + 2] = c1.z;
  uvsData[vertexCount * 2 + 0] = uv1.x;
  uvsData[vertexCount * 2 + 1] = uv1.y;
  vertexCount++;

  PosData[vertexCount * 3 + 0] = p2.x;
  PosData[vertexCount * 3 + 1] = p2.y;
  PosData[vertexCount * 3 + 2] = p2.z;
  colData[vertexCount * 3 + 0] = c2.x;
  colData[vertexCount * 3 + 1] = c2.y;
  colData[vertexCount * 3 + 2] = c2.z;
  uvsData[vertexCount * 2 + 0] = uv2.x;
  uvsData[vertexCount * 2 + 1] = uv2.y;
  vertexCount++;

  PosData[vertexCount * 3 + 0] = p3.x;
  PosData[vertexCount * 3 + 1] = p3.y;
  PosData[vertexCount * 3 + 2] = p3.z;
  colData[vertexCount * 3 + 0] = c3.x;
  colData[vertexCount * 3 + 1] = c3.y;
  colData[vertexCount * 3 + 2] = c3.z;
  uvsData[vertexCount * 2 + 0] = uv3.x;
  uvsData[vertexCount * 2 + 1] = uv3.y;
  vertexCount++;
}

void RenderObject::AddQuad(Vert v1, Vert v2, Vert v3, Vert v4)
{
  AddTriangle(v1, v2, v4);
  AddTriangle(v2, v3, v4);
}

void RenderObject::Clear()
{
  vertexCount = 0;
}

void RenderObject::AssignTexture(char *bmpFile)
{
  SDL_Surface *tex;
  GLuint texID = -1;
  if (tex = SDL_LoadBMP(bmpFile))
  {
    glGenTextures(1, &texID);
    //Turn pink pixels transparent and upload texture to GL
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

        if (r == 255 && g == 0 && b == 255)
        {
          //Transparent
          a = 0;
          //Find neighbor and use color
          int fixRadius = 2;
          //for (int ny = -1; ny <= 1; ny++)
          for (int ny = -fixRadius; ny <= fixRadius; ny++)
          {
            //for (int nx = -1; nx <= 1; nx++)
            for (int nx = -fixRadius; nx <= fixRadius; nx++)
            {
              if (_TexelExists(pixels, w, h, x + nx, y + ny))
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

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(tex);
    delete[] img;
  }
  texture = texID;
}

void RenderObject::UploadToGPU()
{
  glBindBuffer(GL_ARRAY_BUFFER, posDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), PosData, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, colDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), colData, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, uvsDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(GLfloat), uvsData, GL_STATIC_DRAW);
}

void RenderObject::Render()
{
  // bind shader
  glUseProgram(gProgramID);

  //enable Shader Attribute channels
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  //upload camera uniform
  cam &cam = *cam::GetInstance();
  Vec4 ShaderCam(cam.x, cam.y, cam.z, (SCREEN_HEIGHT + 0.0f) / SCREEN_WIDTH);
  glUniform4fv(gLocCAM, 1, (GLfloat*)&ShaderCam);

  //configure vertex attributes
  //attrib number, count, type, normalised?, stride, array buffer-object

  //vertex positions
  glBindBuffer(GL_ARRAY_BUFFER, posDataGLPtr);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //vertex UVs
  glBindBuffer(GL_ARRAY_BUFFER, uvsDataGLPtr);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //vertex colors
  glBindBuffer(GL_ARRAY_BUFFER, colDataGLPtr);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //bing texture
  glBindTexture(GL_TEXTURE_2D, texture);

  //draw data
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);

  PolyCount += vertexCount / 3;

  //Unbind Vert Shader Attributes
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  //Unbind shader
  glUseProgram(NULL);
}

void RenderObject::Destroy()
{
  delete[]PosData;
  delete[]colData;
  delete[]uvsData;
}



int Renderer_GetPolyDrawCount()
{
  int t = PolyCount;
  PolyCount = 0;
  return t;
}

void _printProgramLog(GLuint program)
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
    char *infoLog = new char[maxLength];

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

void _printShaderLog(GLuint shader)
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

bool _initGL()
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
    _printShaderLog(vertexShader);
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
    _printShaderLog(fragmentShader);
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
    _printProgramLog(gProgramID);
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
  gLocCAM = glGetUniformLocation(gProgramID, "CAM");

  gLocTextureSampler = glGetUniformLocation(gProgramID, "TextureSampler");

  //Initialize clear color
  glClearColor(0.f, 0.0, 0.0, 1.f);

  //success
  return true;
}

bool Renderer_Initialise()
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
  gWindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | (SDL_WINDOW_FULLSCREEN * FULL_SCREEN));
  if (gWindow == NULL)
  {
    printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //SDL_SetWindowBordered(gWindow, SDL_FALSE);


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
  if (SDL_GL_SetSwapInterval(USE_VSYNC) < 0)
  {
    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
  }

  //Initialize OpenGL
  if (!_initGL())
  {
    printf("Error: Unable to initialize OpenGL!\n");
    return false;
  }

  //Successful init
  return true;
}

void Renderer_Destroy()
{
  //Deallocate program
  glDeleteProgram(gProgramID);

  //Destroy window	
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  //Quit SDL
  SDL_Quit();
}

void Renderer_Clear()
{
  //Clear color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_Swap()
{
  SDL_GL_SwapWindow(gWindow);
  if(USE_VSYNC)
    glFinish();
}

bool _TexelExists(uint8_t *img, int w, int h, int x, int y)
{
  if ((x < 0) | (y < 0) | (x >= w) | (y >= h))
    return false;
  uint8_t r = img[(x + y *w) * 3 + 2];
  uint8_t g = img[(x + y *w) * 3 + 1];
  uint8_t b = img[(x + y *w) * 3 + 0];
  uint8_t a = 255;
  if (r == 255 && g == 0 && b == 255)
    return false;
  return true;
}
