#include "InputHandler.h"

InputManager::InputManager()
{
  // Empty Constructor
}

void InputManager::Update(const float& timeDelta)
{
  for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++)
    m_previousKeyMap[it->first] = it->second;

  SDL_PumpEvents(); // we need the LATEST mouse pos

  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
    case SDL_QUIT:
      m_exitCommand = true;
      break;

    case SDL_MOUSEMOTION:
      SetMouseCoords(e.motion.x, e.motion.y);
      break;

    case SDL_KEYDOWN:
      PressKey(e.key.keysym.sym);
      break;

    case SDL_KEYUP:
      ReleaseKey(e.key.keysym.sym);
      break;

    case SDL_MOUSEBUTTONDOWN:
      PressKey(e.button.button);
      break;

    case SDL_MOUSEBUTTONUP:
      ReleaseKey(e.button.button);
      break;

    case SDL_MOUSEWHEEL:
      SetMouseScroll(e.wheel.y);
      break;
    }
  }

  // didn't double click in enough time
  if (m_doubleClicker.doubleClickTimer > 0.0f)
  {
    m_doubleClicker.doubleClickTimer -= timeDelta;
    if (m_doubleClicker.doubleClickTimer <= 0.0f)
    {
      m_doubleClicker.doubleClickKey = SDLK_UNKNOWN;
      m_doubleClicker.doubleClickPrev = SDLK_UNKNOWN;
    }
  }

  SDL_GetMouseState(&m_mouseCoords.x, &m_mouseCoords.y);

}

void InputManager::PressKey(unsigned int keyID)
{
  m_keyMap[keyID] = true;

  // Not held down from prev frame and prev = keyID
  if (m_doubleClicker.doubleClickPrev == keyID)
  {
    if (m_doubleClicker.doubleClickTimer > 0.0f)
      m_doubleClicker.doubleClickKey = keyID;
    else
      m_doubleClicker.doubleClickPrev = SDLK_UNKNOWN;

    m_doubleClicker.ignoreNextRelease = true;
  }
}

void InputManager::ReleaseKey(unsigned int keyID)
{
  m_keyMap[keyID] = false;

  if (!m_doubleClicker.ignoreNextRelease)
  {
    m_doubleClicker.doubleClickPrev = keyID;
    m_doubleClicker.doubleClickTimer = m_doubleClicker.timeToDoubleClick;
  }
  else
    m_doubleClicker.ignoreNextRelease = false;
}

void InputManager::SetMouseCoords(int x, int y)
{
  m_mouseCoords.x = x;
  m_mouseCoords.y = y;
}

bool InputManager::IsKeyDown(unsigned int keyID)
{
  auto it = m_keyMap.find(keyID);

  if (it != m_keyMap.end())
    return it->second;

  return false;
}

bool InputManager::IsKeyPressed(unsigned int keyID)
{
  if (IsKeyDown(keyID) && !WasKeyDown(keyID))
    return true;
  return false;
}

bool InputManager::IsKeyReleased(unsigned int keyID)
{
  if (!IsKeyDown(keyID) && WasKeyDown(keyID))
    return true;
  return false;
}

bool InputManager::IsDoubleClicked(unsigned int keyID)
{
  bool ret = m_doubleClicker.doubleClickKey == keyID;

  if (ret)
  {
    m_doubleClicker.doubleClickTimer = 0.0f;
    m_doubleClicker.doubleClickKey = SDLK_UNKNOWN;
    m_doubleClicker.doubleClickPrev = SDLK_UNKNOWN;
  }

  return ret;
}

bool InputManager::WasKeyDown(const unsigned int& keyID)
{
  auto it = m_previousKeyMap.find(keyID);

  if (it != m_previousKeyMap.end())
    return it->second;

  return false;
}