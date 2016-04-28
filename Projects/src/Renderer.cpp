#pragma region Build Options

#define GLEW_STATIC

#pragma endregion

#pragma region includes

#include "Renderer.h"

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

//Program name
const char* PROGRAM_NAME = "Gnomoria";

#define testWindow

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

GLuint vertPosDataGLPtr = 0;
GLuint colPosDataGLPtr = 0;
GLuint UVPosDataGLPtr = 0;
GLfloat* vertPosData = nullptr;
GLfloat* colPosData = nullptr;
GLfloat* UVPosData = nullptr;
GLuint VertexCount = 0;
GLuint TextureID;


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
  gLocMVP = glGetUniformLocation(gProgramID, "MVP");
  gLocCAM = glGetUniformLocation(gProgramID, "CAM");

  gLocTexture = glGetUniformLocation(gProgramID, "TextureSampler");

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

void Renderer_Render()
{
  //Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return;

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
  View = Camera_GetCameraMatrix();
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

void Renderer_Swap()
{
  SDL_GL_SwapWindow(gWindow);
}

void Renderer_AddQuad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4, Vec2 uv1, Vec2 uv2, Vec2 uv3, Vec2 uv4)
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

void Renderer_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset /*= 0*/, int ypixoffset /*= 0*/)
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

  Renderer_AddQuad(
    // Position
    Vec3(isoX + x, (float)isoY, isoZ / 2.0f + y),
    Vec3(isoX + 2 + x, (float)isoY, isoZ / 2.0f + y),
    Vec3(isoX + 2 + x, (float)isoY, isoZ / 2.0f + 2.0f + y),
    Vec3(isoX + x, (float)isoY, isoZ / 2.0f + 2.0f + y),
    // Color
    Vec3(col.r, col.g, col.b),
    Vec3(col.r, col.g, col.b),
    Vec3(col.r, col.g, col.b),
    Vec3(col.r, col.g, col.b),
    // UV
    Vec2(u, v),
    Vec2(u + iATW, v),
    Vec2(u + iATW, v + iATW),
    Vec2(u, v + iATW)
  );
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

GLuint Renderer_LoadTexture(char * path)
{
  SDL_Surface *tex;
  GLuint texID = -1;
  if (tex = SDL_LoadBMP(path))
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
          int fixRadius = 8;
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
  return texID;
}

void Renderer_SetTextureID(GLuint texID)
{
  TextureID = texID;
}

void Renderer_GenBuffers()
{
  glGenBuffers(1, &vertPosDataGLPtr);
  glGenBuffers(1, &UVPosDataGLPtr);
  glGenBuffers(1, &colPosDataGLPtr);
}

void Renderer_CreateBuffers(int verts)
{
  vertPosData = new GLfloat[verts * 3];
  UVPosData = new GLfloat[verts * 2];
  colPosData = new GLfloat[verts * 3];
}

void Renderer_DestroyBuffers()
{
  delete[] vertPosData;
  delete[] UVPosData;
  delete[] colPosData;
}

void Renderer_BindShiz()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 3 * sizeof(GLfloat), vertPosData, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, UVPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 2 * sizeof(GLfloat), UVPosData, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, colPosDataGLPtr);
  glBufferData(GL_ARRAY_BUFFER, VertexCount * 3 * sizeof(GLfloat), colPosData, GL_STATIC_DRAW);
}
