#include "Renderer.h"
#include "World.h"
#include "Camera.h"
#include "Text.h"
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
  Text_Initialize();

  cam &camera = *cam::GetInstance();
  camera = Vec3(0, 10, 0);

  //Main loop flag
  bool running = true;

  //Event handler
  SDL_Event e;

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

    //Handle mouse input
    int mousex;
    int mousey;
    bool mouseleft;
    bool mouseright;
    int scroll = 0;
    uint32_t mouseflags = SDL_GetMouseState(&mousex, &mousey);
    mouseleft = mouseflags & SDL_BUTTON(SDL_BUTTON_LEFT);
    mouseright = mouseflags & SDL_BUTTON(SDL_BUTTON_RIGHT);
    camera.UpdateMouseControls(mousex, mousey, mouseleft, mouseright, scroll);

    //Handle keyboard input
    const static unsigned char *keyboard = SDL_GetKeyboardState(NULL);
    camera.UpdateKeyboardControls(keyboard);
    if (camera.y > 80) camera.y = 80;
    if (camera.y < 6) camera.y = 6;



    //Render
    Renderer_Clear();
    World_Draw();

    Text_Draw("Gnomoria!", Vec2(-60.0f,-85.0f), 120 );

    Renderer_Swap();

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
