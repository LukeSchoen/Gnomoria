#include <time.h>
#include "text.h"
#include <stdio.h>
#include <stdint.h>

static int frameRate = 0;
static int lastFrame = 0;
static int frames = 0;
static char text[32];

void UpdateFrameRate()
{
  frames++;
  if (clock() - lastFrame > 1000)
  {
    frameRate = frames;
    frames = 0;
    lastFrame = clock();
  }
  
  sprintf(text, "%d", frameRate);
  float Aspect = (SCREEN_WIDTH / (SCREEN_HEIGHT + 0.0));
  Text_Draw(text, Vec2(-Aspect, -1), 0.5);
}