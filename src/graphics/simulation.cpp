#include "graphics/simulation.hpp"


void Simulation::setup()
{
  m_world.setup(40, 40, 20);
  
  m_line = sf::VertexArray(sf::LineStrip, 2);
  m_line[0].color = sf::Color(200, 50, 50);
  m_line[1].color = sf::Color(50, 200, 50);

  m_to.setRadius(m_radius);
  m_to.setOrigin(sf::Vector2f(m_radius, m_radius));
  m_to.setFillColor(sf::Color(50, 200, 50));
  
  m_from.setRadius(m_radius);
  m_from.setOrigin(sf::Vector2f(m_radius, m_radius));
  m_from.setFillColor(sf::Color(200, 50, 50));
  m_from.setPosition(0.0f, 0.0f);

  m_intersect.setRadius(m_radius);
  m_intersect.setOrigin(sf::Vector2f(m_radius, m_radius));
  m_intersect.setOutlineThickness(1);
  m_intersect.setOutlineColor(sf::Color(200, 200, 50));
  m_intersect.setFillColor(sf::Color(0, 0, 0, 0));
}

void Simulation::run(float dt)
{
  m_world.update(m_renderer);
  
  sf::Vector2f mouse_pos = m_renderer.mapPixelToCoords(sf::Mouse::getPosition(m_renderer));
  if (m_world.get_bounds().contains(mouse_pos))
    m_to.setPosition(mouse_pos);
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    m_from.move(0.0f, -m_move_vel * dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    m_from.move(-m_move_vel * dt, 0.0f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    m_from.move(0.0f, m_move_vel * dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    m_from.move(m_move_vel * dt, 0.0f);  
  
  m_line[0].position = m_from.getPosition();
  m_line[1].position = m_to.getPosition();
  
  m_renderer.clear(sf::Color::Black);
  
  m_world.draw(m_renderer);
  m_renderer.draw(m_line);
  m_renderer.draw(m_to);
  m_renderer.draw(m_from);
  
  sf::Vector2f intersect;
  if (m_world.cast(intersect, m_from.getPosition(), m_to.getPosition())) {
    m_intersect.setPosition(intersect);
    m_renderer.draw(m_intersect);
  }
  
  m_renderer.display();
}

void Simulation::event()
{
  sf::Texture texture;
  sf::Image image;

  switch (m_event.type) {
    
    case sf::Event::KeyPressed:
      switch (m_event.key.code) {
        
        case sf::Keyboard::Space:
          texture.create(m_size.x, m_size.y);
          texture.update(m_renderer);
          image = texture.copyToImage();
          image.saveToFile("example.png");
          break;

        default:
          break;
      
      }
      break;

    default:
      break;

  }
}

void Simulation::clear()
{
}

