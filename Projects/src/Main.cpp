#include "Renderer.h"
#include "Audio.h"
#include "World.h"
#include "WorldAccess.h"
#include "WorldDraw.h"
#include "Camera.h"
#include "Text.h"
#include "SDL.h"
#include <glm.hpp>
#include <stdio.h>
#include "InputHandler.h"
#include "Cursor.h"
#include "FrameRate.h"
#include "Debug.h"
#include "perlinNoise.h"


//Main Loop
int wmain(int argc, char *argv[])
{
  if (!Renderer_Initialise()) {printf("Failed to initialize!\n"); getchar(); return 1;}

  Audio_PlayMP3("Assets\\music\\DaysWork.mp3");

  PerlinNoiseGenerator worldNoiseGenerator;
  uint8_t * worldNoise = worldNoiseGenerator.GeneratePerlinNoise(256, 256, 10);



  World_LoadWorld();
  Text_Initialize();

  cam &camera = *cam::GetInstance();
  camera = Vec3(0, 10, 0);

  InputManager input;


  WorldAccess& gameWorld = *WorldAccess::GetInstance();
  gameWorld.Load("Assets\\Worlds\\test");
  WorldDraw worldDrawer = *WorldDraw::GetInstance();

  RenderObject chunk = worldDrawer.BuildRegionMesh(Vec2i(-256, -256), Vec2i(128, 128), 128);
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
