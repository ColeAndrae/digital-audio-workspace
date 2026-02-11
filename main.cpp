#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode({800, 800}), "DAW");

sf::SoundBuffer E4Buffer;
sf::SoundBuffer B4Buffer;
sf::SoundBuffer Gb4Buffer;

int main() {

  std::vector<int16_t> E4;
  for (int i = 0; i < 44100; i++) {
    E4.push_back(i % 266 < 133 ? 10000 : -10000);
  }

  std::vector<int16_t> B4;
  for (int i = 0; i < 44100; i++) {
    B4.push_back(i % 180 < 90 ? 10000 : -10000);
  }

  std::vector<int16_t> Gb4;
  for (int i = 0; i < 44100; i++) {
    Gb4.push_back(i % 240 < 120 ? 10000 : -10000);
  }

  (void)E4Buffer.loadFromSamples(
      E4.data(), E4.size(), 2, 30000,
      {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight});

  (void)B4Buffer.loadFromSamples(
      B4.data(), B4.size(), 2, 30000,
      {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight});

  (void)Gb4Buffer.loadFromSamples(
      Gb4.data(), Gb4.size(), 2, 30000,
      {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight});

  sf::Sound E4Player(E4Buffer);
  sf::Sound B4Player(B4Buffer);
  sf::Sound Gb4Player(Gb4Buffer);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Space) {
          E4Player.play();
          B4Player.play();
          Gb4Player.play();
        }
      }
    }
    window.clear();
    window.display();
  }

  return 0;
}
