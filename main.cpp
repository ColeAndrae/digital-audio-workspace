#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode({800, 800}), "DAW");

sf::SoundBuffer buffer;

int main() {

  std::vector<int16_t> sound;
  for (int i = 0; i < 44100; i++) {
    sound.push_back(i % 100 < 50 ? 5000 : -5000);
  }

  (void)buffer.loadFromSamples(
      sound.data(), sound.size(), 2, 44100,
      {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight});

  sf::Sound player(buffer);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Space) {
          player.play();
        }
      }
    }
    window.clear();
    window.display();
  }

  return 0;
}
