#include <cstdlib>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Cell.h"

const unsigned WindowDimen[] = {800,600};

void renderWorld(World world, sf::RenderWindow& window, sf::RectangleShape square);
void seedWorld(World& world);

int main(int argc, char** argv)
{
  srand(1807);
  World world(WindowDimen[0]/10,WindowDimen[1]/10);
  world.addType();
  seedWorld(world);
  sf::RenderWindow window(sf::VideoMode(WindowDimen[0],WindowDimen[1]), "CellSpace");
  window.setFramerateLimit(10);
  sf::RectangleShape square(sf::Vector2f(10, 10));
  square.setFillColor(sf::Color::Green);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	window.close();
    }
    window.setActive();
    window.clear(sf::Color::Black);
    renderWorld(world, window, square);
    window.display();
    world.Iterate();
  }
  return 0;
}

void renderWorld(World world, sf::RenderWindow& window, sf::RectangleShape square)
{
  std::vector<int> data = world.getWorldWithID();
    float x = 0;
    float y = 0;
    for (unsigned k = 0; k < data.size(); k++)
    {
      if (data[k] == 1)
      {
	square.setPosition(x,y);
	window.draw(square);
      }
      x = (x + 10);
      if (x == WindowDimen[0])
      {
	y = y + 10;
	x = 0;
      }
    }
}

void seedWorld(World& world)
{
  std::vector<int> seed(WindowDimen[0]/10 * WindowDimen[1]/10, 0);
  for (unsigned i = 0; i < seed.size(); i++)
  {
    unsigned k = rand()%20;
    if (k == 0)
      seed[i] = 1;
  }
  world.SeedWorld(seed);
}