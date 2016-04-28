#include "Renderer.h"
#include "World.h"
#include "Camera.h"

#include "SDL.h"

#include <glm.hpp>
#include <stdio.h>
#include <time.h>

//Main Loop
int wmain(int argc, char *argv[])
{  
  if (!Renderer_Initialise())
  {
    printf("Failed to initialize!\n");
    getchar();
    return 1;
  }

  World_LoadWorld();

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
    }

    //Handle keyboard input
    const static unsigned char *keyboard = SDL_GetKeyboardState(NULL);
    glm::vec3 camOff;

    {//3d movement
      camOff = Camera_CameraKeyboardControls(keyboard);
      camPos += camOff;

      if (camPos.y > 80)
        camPos.y = 80;

      if (camPos.y < 6)
        camPos.y = 6;

    }

    //Render
    Renderer_Render();

    static int lastFrame = 0;
    static int frames = 0;
    frames++;
    if (clock() - lastFrame > 1000)
    {
      printf("%d\n\n", frames);
      frames = 0;
      lastFrame = clock();
    }
  }

  //Free engine resources
  Renderer_Destroy();

  return 0; // return success!
}
