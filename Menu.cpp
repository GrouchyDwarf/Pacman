#include"Menu.h"

Menu::Menu(const sf::RenderWindow& window) {
	isMenu = true;
	button = "";
	menuTexture.loadFromFile("image/menu.png");
	aboutTexture.loadFromFile("image/about.png");
	playTextTexture.loadFromFile("image/text_play.png");
	aboutTextTexture.loadFromFile("image/text_about.png");
	exitTextTexture.loadFromFile("image/text_exit.png");
	menu.setTexture(menuTexture);
	about.setTexture(aboutTexture);
	playText.setTexture(playTextTexture);
	aboutText.setTexture(aboutTextTexture);
	exitText.setTexture(exitTextTexture);
	playText.setPosition(window.getSize().x/2.2,window.getSize().y / 1.7);
	aboutText.setPosition(window.getSize().x / 2.35, window.getSize().y / 1.42);
	exitText.setPosition(window.getSize().x / 2.2, window.getSize().y / 1.2);
}

void Menu::start(sf::RenderWindow& window) {
	while (isMenu) {
		//убираем вечную прогрузку
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		playText.setColor(sf::Color::Yellow);
		aboutText.setColor(sf::Color::Yellow);
		exitText.setColor(sf::Color::Yellow);
		if (sf::IntRect(window.getSize().x/2.2, window.getSize().y/1.7, 114, 78).contains(sf::Mouse::getPosition(window))) {
			playText.setColor(sf::Color(255, 140, 0));
			button = "play";
		}
		if (sf::IntRect(window.getSize().x / 2.35, window.getSize().y / 1.42, 164, 78).contains(sf::Mouse::getPosition(window))) {
			aboutText.setColor(sf::Color(255, 140, 0));
			button = "about";
		}
		if (sf::IntRect(window.getSize().x / 2.2, window.getSize().y / 1.2, 104, 78).contains(sf::Mouse::getPosition(window))) {
			exitText.setColor(sf::Color(255, 140, 0));
			button = "exit";
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (button == "play") isMenu = false;
			if (button == "about") {
				window.draw(about);
				window.display();
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			}
			if (button == "exit") {
				window.close();
				isMenu = false;//чтобы программа завершилась корректно,а не просто закрылось окно
			}
		}
		window.draw(menu);
		window.draw(playText);
		window.draw(aboutText);
		window.draw(exitText);
		window.display();
	}
}