#include "graphics/engine.hpp"


void Engine::create(int width, int height, std::string title)
{
  m_size = {(float)width, (float)height};

  int style = sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar;
  sf::VideoMode shape(m_size.x, m_size.y);
  sf::ContextSettings context;
  context.antialiasingLevel = 4;

  m_renderer.create(shape, title, style, context);
  m_renderer.setFramerateLimit(60);
  m_renderer.setKeyRepeatEnabled(false);

  m_view.setSize({m_size.x, m_size.y});
  m_view.setCenter(sf::Vector2f(0.0f, 0.0f));
  m_renderer.setView(m_view);
}

void Engine::main_loop()
{
  setup();

  float dt;
  while (m_renderer.isOpen()) {
    dt = m_clock.restart().asSeconds();

    while (m_renderer.pollEvent(m_event)) {
      handle_event();
      event();
    }

    run(dt);
  }

  clear();
}

void Engine::handle_event()
{
  switch (m_event.type) {      
    case sf::Event::Closed:
      m_renderer.close();
      break;
    case sf::Event::Resized:
      m_size = {(float)m_event.size.width, (float)m_event.size.height};
      m_view.setSize({m_size.x, m_size.y});
      m_renderer.setView(m_view);
      break;
    default:
      break;
  }
}

