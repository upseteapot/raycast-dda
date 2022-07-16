#pragma once
#include <SFML/Graphics.hpp>

#include "graphics/engine.hpp"
#include "graphics/raycast_world.hpp"


class Simulation : public Engine
{
  public:
    Simulation() = default;

  private:
    float m_radius = 8.0f;
    float m_move_vel = 100.0f;

    RaycastWorld m_world;
    sf::VertexArray m_line;
    sf::CircleShape m_intersect, m_from, m_to;

    void setup() override;
    void run(float dt) override;
    void event() override;
    void clear() override;
};

