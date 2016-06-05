#include "Renderer.h"
#include "Audio.h"
#include "World.h"
#include "WorldAccess.h"
#include "WorldDraw.h"
#include "WorldGenerator.h"
#include "Camera.h"
#include "Text.h"
#include "SDL.h"
#include <stdio.h>
#include "InputHandler.h"
#include "Cursor.h"
#include "FrameRate.h"
#include "Debug.h"
#include "perlinNoise.h"
#include "Image.h"


//Main Loop
int wmain(int argc, char *argv[])
{
  testworldgen();

  if (!Renderer_Initialise()) {printf("Failed to initialize!\n"); getchar(); return 1;}

  //Audio_PlayMP3("Assets\\music\\DaysWork.mp3");

  World_LoadWorld();
  Text_Initialize();

  cam &camera = *cam::GetInstance();
  camera = Vec3(0, 10, 0);

  InputManager input;

  //Create World
  WorldGenerator &worldGen = *WorldGenerator::GetInstance();
  //worldGen.Create("newTest", Vec3i(1024, 256, 1024));

  //Open World
  WorldAccess &gameWorld = *WorldAccess::GetInstance();
  gameWorld.Load("newTest");

  //Generate World Data
  //worldGen.GenerateWorld();


  //Draw World
  WorldDraw &worldDrawer = *WorldDraw::GetInstance();
  RenderObject chunk = worldDrawer.BuildRegionMesh(Vec2i(0, 0), Vec2i(256, 256), 1);
  chunk.UploadToGPU();

  printf("%d\n", gameWorld.GetBlock( Vec3i(0,55,0) ).floorType);




  SDL_ShowCursor(0);
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

  //Main loop flag
  bool running = true;

  while (running)
  {
    //Get user input
    input.Update(0.0f);

    //Has User Closed program?
    running = !(input.Exit() | input.IsKeyDown(SDLK_ESCAPE));

    //Render
    Renderer_Clear();
    World_Draw();
    Debug_Draw();
    chunk.Render();

    Text_Draw("Gnomoria!", Vec2(-60.0f, -85.0f), 120, true);

    //Handle mouse input
    camera.UpdateMouseControls(input.GetMouseCoords(), input.IsKeyDown(SDL_BUTTON_LEFT), input.IsKeyDown(SDL_BUTTON_RIGHT), input.GetMouseScroll());

    //Handle keyboard input
    const static unsigned char *keyboard = SDL_GetKeyboardState(NULL);
    camera.UpdateKeyboardControls(keyboard);
    //if (camera.y > 80) camera.y = 80;
    //if (camera.y < 6) camera.y = 6;

    UpdateFrameRate();

    input.Update(0.0f); //Update Mouse Pos
    Cursor_DrawCursor(input.GetMouseCoords(), 2.0);
    Renderer_Swap();
  }

  //Free engine resources
  Renderer_Destroy();

  return 0; // return success!
}
