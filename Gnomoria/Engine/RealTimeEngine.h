#ifndef RealTimeEngine_h__
#define RealTimeEngine_h__

#include <cstdint>

class Engine;

class RealTimeEngine
{
  uint32_t m_lastTicks;
  uint32_t m_ticks;
  uint32_t m_coreSpeed = 60;
  Engine* m_engine;
  bool m_running = true;

public:
  RealTimeEngine();

  void Start();
  void Stop();
  void Step();
};
#endif // RealTimeEngine_h__