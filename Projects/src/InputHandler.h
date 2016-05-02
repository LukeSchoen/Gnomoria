#pragma once

#include <SDL.h>
#include "Math/Vector.h"
#include <unordered_map>

class InputManager
{
public:
  InputManager();

  void Update(const float& timeDelta);

  bool IsKeyDown(unsigned int keyID);		///< Returns true if key is held down
  bool IsKeyPressed(unsigned int keyID);	///< Returns true if key is pressed once
  bool IsKeyReleased(unsigned int keyID);	///< Returns true if released
  bool IsDoubleClicked(unsigned int keyID);

  const Vec2i& GetMouseCoords() const { return m_mouseCoords; }
  int GetMouseScroll() { int ret = m_scroll; m_scroll = 0; return ret; }

  bool Exit() { return m_exitCommand; }
private:
  void PressKey(unsigned int keyID);
  void ReleaseKey(unsigned int keyID);
  void SetMouseCoords(int x, int y);
  void SetMouseScroll(int scroll) { m_scroll = scroll; }

  bool WasKeyDown(const unsigned int& keyID);

  SDL_Event e;

  std::unordered_map<unsigned int, bool> m_keyMap;
  std::unordered_map<unsigned int, bool> m_previousKeyMap;
  Vec2i m_mouseCoords;
  int m_scroll = 0;
  bool m_exitCommand = false;

  struct doubleClick
  {
    float doubleClickTimer = 0.0f;
    const float timeToDoubleClick = 0.2f;

    unsigned int doubleClickPrev = SDLK_UNKNOWN;
    unsigned int doubleClickKey = SDLK_UNKNOWN;
    bool ignoreNextRelease = false;
  } m_doubleClicker;
};

