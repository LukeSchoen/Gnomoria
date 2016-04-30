#ifndef Text_h__
#define Text_h__

#include "renderer.h"

void Text_Initialize();

void Text_Destroy();

void Text_Draw(char* text, Vec2 pos, int fontSize);

void Text_Draw(char* text, Vec2 pos, Vec2 size);

#endif // Text_h__