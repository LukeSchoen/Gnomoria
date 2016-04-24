#include "RealTimeEngine.h"
#include <time.h>

RealTimeEngine::RealTimeEngine()
  : m_lastTicks(0)
  , m_ticks(0)
{
  Start();
}

void RealTimeEngine::Start()
{
  m_ticks = clock();
  m_lastTicks = m_ticks;
}

void RealTimeEngine::Step()
{
  if (m_running && m_engine != nullptr)
  {
    m_ticks = clock();
    for (uint32_t i = 0; i < (m_ticks - m_lastTicks) / (1000 / m_coreSpeed); i++)
    {
      //Step Game World
    }
    m_lastTicks += (m_ticks - m_lastTicks) / (1000 / m_coreSpeed) * (1000 / m_coreSpeed);
  }

}

void RealTimeEngine::Stop()
{
  m_running = false;
}
