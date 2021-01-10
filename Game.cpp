#include"Game.h"
#include<iostream>
#include<vector>

Game::Game(const sf::Vector2f& size):pacman(labyrinth),inky(labyrinth),pinky(labyrinth),blinky(labyrinth),clyde(labyrinth) {
	ghosts = { &inky,&pinky,&blinky,&clyde };
	gameState = GameState::PLAY;
	cookieCount = 0;
	bool successfulFontLoading = font.loadFromFile("doc/times.ttf");
	bool successfulImageLoading = gameOverBackgroundT.loadFromFile("image/game_over.png");
	if (!successfulFontLoading || !successfulImageLoading) {
		std::cerr << "Loading error!!!";
		exit(1);
	}
	cookieCount = labyrinth.getRemainingCookies();
	gameOverBackground.setTexture(gameOverBackgroundT);
	gameOverBackground.setPosition(0, 0);
	board.setFont(font);
	board.setFillColor(sf::Color::White);
	board.setPosition(size.x / 2.0,size.y/1.4);
	board.setCharacterSize(50);
	counter.setPosition(size.x - 15,10);
	counter.setFont(font);
	counter.setCharacterSize(20);
	counter.setFillColor(sf::Color::White);
}

void Game::refreshBoard(sf::Text& board,sf::Text&counter, const std::string& text) {
	board.setString(text);
	counter.setString(std::to_string(this->getRemainingCookies()));
	//ровняем текст(чтобы начинался чуть раньше)
	board.setOrigin(board.getLocalBounds().width / 2, board.getLocalBounds().height / 2);
	counter.setOrigin(counter.getLocalBounds().width / 2, counter.getLocalBounds().height / 2);
}

void Game::refresh(float time) {
	if (gameState == GameState::PLAY) {
		pacman.refresh(time, labyrinth);
		for (int i = 0; i < ghosts.size();++i) {
			ghosts[i]->refresh(time,labyrinth);
			if (ghosts[i]->getBoards().intersects(pacman.getBoards())) {//условие поражения(то есть столкновение пакмена и приведения)
				gameState = GameState::LOSE;
			}
		}
		for (int i = 0; i < ghosts.size() - 1;++i) {
			for (int j = i + 1; j < ghosts.size();++j) {
				if (ghosts[i]->getBoards().intersects(ghosts[j]->getBoards())) {
					ghosts[j]->changeOppositeDirection();
					ghosts[i]->changeOppositeDirection();
				}
			}
		}
		if (!(*this).getRemainingCookies()) {//условие победы(все печенье съедено)
			gameState = GameState::WIN;
		}
		this->refreshBoard(board,counter,getBoard());
	}
}

unsigned int Game::getRemainingCookies() {
	return cookieCount - pacman.getEatenCookies();
}

std::string Game::getBoard() {
	std::string board;
	switch (gameState) {
	case GameState::WIN:
		board = "You win!";
		break;
	case GameState::LOSE:
		board = "You lose!" + std::to_string(this->getRemainingCookies()) + " cookies left";
		break;
	case GameState::PLAY:
		board = std::to_string(this->getRemainingCookies()) + " cookies left";
		break;
	}
	return board;
}

void Game::draw(sf::RenderWindow& window) {
	labyrinth.draw(window);
	pacman.draw(window);
	for (int i = 0; i < ghosts.size();++i) 
		ghosts[i]->draw(window);
	if ((gameState == GameState::LOSE) || (gameState==GameState::WIN)) {
		window.draw(gameOverBackground);
		window.draw(board);
	}
	if(gameState == GameState::PLAY)
	    window.draw(counter);
}

Game::~Game() {
	
}