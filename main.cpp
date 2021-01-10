#include<SFML/Graphics.hpp>
#include"Game.h"

int main() {
	sf::RenderWindow window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	window.create(sf::VideoMode(960, 960), "PacMan", sf::Style::Close, settings);
	sf::Clock clock;
	Menu menu(window);
	menu.start(window);
	Game game({960, 960});
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		const float elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		game.refresh(elapsedTime);

		window.clear();
		game.draw(window);

		window.display();

	};
}