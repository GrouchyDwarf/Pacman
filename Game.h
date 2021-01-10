#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include"Pacman.h"
#include"Ghost.h"
#include"Menu.h"

class Game {
	Labyrinth labyrinth;
	Pacman pacman;
	Inky inky;
	Pinky pinky;
	Blinky blinky;
	Clyde clyde;
	std::vector<Ghost*> ghosts;
	enum  GameState {
	    PLAY,
	    WIN,
	    LOSE
    } gameState;
	unsigned int cookieCount;
	sf::Font font;
	sf::Texture gameOverBackgroundT;
	sf::Sprite gameOverBackground;
	sf::Text board;
	sf::Text counter;
public:
	
	Game(const sf::Vector2f& size);
	~Game();
	unsigned int getRemainingCookies();
	void refreshBoard(sf::Text& board,sf::Text& counter,const std::string& text);
	std::string getBoard();//Зависит от состояния игры
	void refresh(float time);
	void draw(sf::RenderWindow& window);
};

#endif // !_GAME_H_
