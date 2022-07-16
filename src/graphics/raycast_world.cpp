#include "graphics/raycast_world.hpp"


RaycastWorld::~RaycastWorld()
{
  if (m_rows * m_cols != 0)
    delete[] m_states;
}

void RaycastWorld::setup(int rows, int cols, int square_size)
{
  m_rows = rows;
  m_cols = cols;
  m_square_size = square_size;

  m_states = new int[m_rows * m_cols];
    
  m_start = -sf::Vector2f(m_cols * m_square_size * 0.5f, m_rows * m_square_size * 0.5f);
  m_bounds = { m_start.x, m_start.y, (float)(m_cols * m_square_size), (float)(m_rows * m_square_size) };

  m_wall_shape.setSize(sf::Vector2f(m_square_size + 1, m_square_size + 1));
  m_wall_shape.setOutlineThickness(-1);
  m_wall_shape.setOutlineColor(sf::Color(25, 25, 25));
  
  m_casted_wall_shape.setSize(sf::Vector2f(m_square_size + 1, m_square_size + 1));
  m_casted_wall_shape.setOutlineThickness(-1);
  m_casted_wall_shape.setOutlineColor(sf::Color(200, 200, 50));
  m_casted_wall_shape.setFillColor(sf::Color(50, 50, 150));
}

void RaycastWorld::update(sf::RenderWindow &renderer)
{
  sf::Vector2f mouse_pos = renderer.mapPixelToCoords(sf::Mouse::getPosition(renderer));
  int index = floor((mouse_pos.x - m_start.x) / m_square_size) + floor((mouse_pos.y - m_start.y) / m_square_size) * m_cols;
  
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_bounds.contains(mouse_pos))
    m_states[index] = 1;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_bounds.contains(mouse_pos))
    m_states[index] = 0;
}

void RaycastWorld::draw(sf::RenderWindow &renderer)
{
  for (int y=0; y < m_rows; y++)
    for (int x=0; x < m_cols; x++) {
      m_wall_shape.setPosition(m_start + sf::Vector2f(x * m_square_size, y * m_square_size));
      if (m_states[x + y * m_cols])
        m_wall_shape.setFillColor(sf::Color(50, 50, 150));
      else
        m_wall_shape.setFillColor(sf::Color(0, 0, 0, 0));
      renderer.draw(m_wall_shape);
    }

  if (m_tile_found) {
    m_casted_wall_shape.setPosition(m_start + static_cast<sf::Vector2f>(m_coords) * (float)m_square_size);
    renderer.draw(m_casted_wall_shape);
  }

}

bool RaycastWorld::cast(sf::Vector2f &intersect, sf::Vector2f from, sf::Vector2f to)
{
  Vec2f start     = sfml_vec2f((from - m_start)) / m_square_size;
  Vec2f dir       = Vec2f::norm(sfml_vec2f((to - from)));
  Vec2f step_size = { sqrt(1 + pow(dir.y / dir.x, 2)), sqrt(1 + pow(dir.x / dir.y, 2)) };
  m_coords        = { (int)floor(start.x), (int)floor(start.y) };
 
  Vec2f ray_length;
  Vec2i step;

  if (dir.x < 0) {
    step.x = -1;
    ray_length.x = (start.x - (float)m_coords.x) * step_size.x;
  } else {
    step.x = 1;
    ray_length.x = ((float)m_coords.x + 1.f - start.x) * step_size.x;
  }

  if (dir.y < 0) {
    step.y = -1;
    ray_length.y = (start.y - (float)m_coords.y) * step_size.y;
  } else {
    step.y = 1;
    ray_length.y = ((float)m_coords.y + 1.f - start.y) * step_size.y;
  }
  
  float max_distance = Vec2f::dist(sfml_vec2f(from), sfml_vec2f(to)) / m_square_size;
  float distance = 0.0f;
  m_tile_found = false;
  while (!m_tile_found && distance < max_distance) {
    if (ray_length.x < ray_length.y) {
      m_coords.x += step.x;
      distance = ray_length.x;
      ray_length.x += step_size.x;
    } else {
      m_coords.y += step.y;
      distance = ray_length.y;
      ray_length.y += step_size.y;
    }
    
    if (0 <= m_coords.x && m_coords.x < m_cols && 0 <= m_coords.y && m_coords.y < m_rows) {
      if (m_states[m_coords.x + m_coords.y * m_cols] == 1) {
        m_tile_found = true;
      }
    }
  }

  if (m_tile_found)
    intersect = vec2f_sfml((start + dir * distance)) * (float)m_square_size + m_start;

  return m_tile_found;
}

const sf::FloatRect &RaycastWorld::get_bounds() const
{
  return m_bounds;
}

