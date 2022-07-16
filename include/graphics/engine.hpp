#pragma once
#include <SFML/Graphics.hpp>


class Engine
{
  public:
    Engine() = default;
    void create(int width, int height, std::string title);
    void main_loop();
    
  protected:
    void handle_event();

    sf::Vector2f m_size;
    sf::RenderWindow m_renderer;
    sf::View m_view;
    sf::Clock m_clock;
    sf::Event m_event;

    virtual void setup() = 0;
    virtual void run(float dt) = 0;
    virtual void event() = 0;
    virtual void clear() = 0;
};

