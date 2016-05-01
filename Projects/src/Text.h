#ifndef Text_h__
#define Text_h__

#include "renderer.h"

void Text_Initialize();

void Text_Destroy();

void Text_Draw(char* text, Vec2 pos, float fontSize, bool inWorld = false);

void Text_Draw(char* text, Vec2 pos, Vec2 size, Vec3 color, bool inWorld);

#endif // Text_h__