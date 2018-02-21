//
//  Author: Shervin Aflatooni
//

#include "FreeLook.h"

FreeLook::FreeLook(float speed)
{
  m_speed = speed;
  setProperty("speed", FLOAT, &m_speed, 0, 0.01);
}

FreeLook::~FreeLook(void)
{
}

void FreeLook::update(Input *input, std::chrono::microseconds delta)
{
  float moveAmount = m_speed * (delta.count() / 1000.f);
#ifdef ANDROID
  if (input->mouseIsPressed(SDL_BUTTON_LEFT))
  {
#else
  if (input->mouseIsPressed(SDL_BUTTON_RIGHT))
  {
#endif
    input->grabMouse();
    glm::vec2 pos = input->getMouseDelta();
    if (pos.y != 0)
    {
      m_parentEntity->getTransform().rotate(glm::vec3(1, 0, 0), -pos.y * moveAmount);
    }
    if (pos.x != 0)
    {
      m_parentEntity->getTransform().setRotation(glm::angleAxis(-pos.x * moveAmount, glm::vec3(0, 1, 0)) * m_parentEntity->getTransform().getRotation());
    }
#ifdef ANDROID
  }
  else if (input->mouseIsReleased(SDL_BUTTON_LEFT))
  {
#else
  }
  else if (input->mouseIsReleased(SDL_BUTTON_RIGHT))
  {
#endif
    input->releaseMouse();
  }
}
