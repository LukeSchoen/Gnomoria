#ifndef Camera_h__
#define Camera_h__

#include "Math/Vector.h"

const float Deg2Rag = 1.0f / 57.2958f;

struct cam : public Vec3
{
  cam(Vec3 Pos);
  static cam *GetInstance();
  void UpdateKeyboardControls(const unsigned char *keyboard);
  void cam::UpdateMouseControls(Vec2i MousePos, bool leftClick, bool rightClick, int scroll);
};

#endif // Camera_h__