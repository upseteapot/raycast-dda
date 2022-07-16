#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "math/vec2.hpp"


class RaycastWorld
{
  public:
    RaycastWorld() = default;
    ~RaycastWorld();

    void setup(int rows, int cols, int square_size);
    void update(sf::RenderWindow &renderer);
    void draw(sf::RenderWindow &renderer); 
    bool cast(sf::Vector2f &intersect, sf::Vector2f from, sf::Vector2f to);
    const sf::FloatRect &get_bounds() const;

  private:
    sf::Vector2f m_start;
    sf::FloatRect m_bounds;

    int m_rows, m_cols;
    int m_square_size;
    int *m_states;
  
    sf::Vector2i m_coords;
    bool m_tile_found;

    sf::RectangleShape m_wall_shape, m_casted_wall_shape;
};

