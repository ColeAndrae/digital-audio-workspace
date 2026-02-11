#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

double PI = 3.1415926535;

sf::RenderWindow window(sf::VideoMode({1200, 720}), "digital audio workspace");

void drawGrid(std::vector<std::vector<bool>> notes) {
  sf::RectangleShape rectangle({1200, 1});
  rectangle.setFillColor(sf::Color::White);

  for (float i = 0; i < 720; i += 20) {
    rectangle.setPosition({0, i});
    window.draw(rectangle);
  }

  rectangle.setSize({1, 720});
  for (float i = 0; i < 1200; i += 20) {
    rectangle.setPosition({i, 0});
    window.draw(rectangle);
  }

  rectangle.setSize({20, 20});
  for (float r = 0; r < 60; r++) {
    for (float c = 0; c < 36; c++) {
      if (notes[r][c]) {
        rectangle.setPosition({r * 20, c * 20});
        window.draw(rectangle);
      }
    }
  }
}

int main() {

  std::vector<std::vector<bool>> notes(60, std::vector<bool>(36, 0));

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        // Play sounds
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        notes[(mousePos.x / 20)][(mousePos.y / 20)] = 1;
      }
    }
    drawGrid(notes);
    window.display();
  }

  return 0;
}
