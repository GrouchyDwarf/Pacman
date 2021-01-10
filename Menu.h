#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include<SFML/Graphics.hpp>

class Menu {
	sf::Texture menuTexture,aboutTexture,playTextTexture, aboutTextTexture, exitTextTexture;
	sf::Sprite menu, about, playText, aboutText, exitText;
	bool isMenu;
    std::string button;
public:
	Menu(const sf::RenderWindow& window);
	void start(sf::RenderWindow& window);
};
#endif // !_MENU_H_
