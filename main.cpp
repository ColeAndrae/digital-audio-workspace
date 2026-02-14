#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

double PI = 3.1415926535;

const int TEMPO = 44100 / 8;
const int VOLUME = 5000;

sf::RenderWindow window(sf::VideoMode({1200, 720}), "digital audio workspace");

std::vector<sf::SoundBuffer> buffers(36);

std::vector<sf::Sound> players;

std::vector<float> frequencies = {
    1661.2, 1568.0, 1480.0, 1397.0, 1318.6, 1244.6, 1174.6, 1108.8, 1046.6,
    987.8,  932.4,  880.0,  830.6,  766.0,  740.0,  698.5,  659.3,  622.3,
    587.3,  554.4,  523.3,  493.9,  466.2,  440.0,  415.3,  392.0,  370.0,
    349.25, 329.65, 311.15, 293.65, 277.2,  261.65, 246.95, 233.1,  220.0};

void playNotes(std::vector<std::vector<bool>> notes) {

  std::vector<std::vector<int16_t>> sounds(36, std::vector<int16_t>());

  for (float r = 0; r < 60; r++) {
    for (float c = 0; c < 36; c++) {
      if (notes[r][c]) {
        for (int i = 0; i < TEMPO; i++) {
          // sounds[c].push_back(VOLUME * sin(PI * frequencies[c] * i / 44100));
          sounds[c].push_back(
              (i % (int)(frequencies[c] * 2) < (int)frequencies[c]) ? VOLUME
                                                                    : -VOLUME);
        }
      } else {
        for (int i = 0; i < TEMPO; i++) {
          sounds[c].push_back(0);
        }
      }
    }
  }

  for (float c = 0; c < 36; c++) {
    (void)buffers[c].loadFromSamples(
        sounds[c].data(), sounds[c].size(), 2, 44100,
        {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight});
    players.push_back(sf::Sound(buffers[c]));
  }

  for (float c = 0; c < 36; c++) {
    players[c].play();
  }
}

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
        if (keyPressed->code == sf::Keyboard::Key::Space) {
          playNotes(notes);
        }
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
