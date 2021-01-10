#pragma once
#ifndef _GHOST_H_
#define _GHOST_H_
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Labyrinth.h"



class Ghost {
protected:
	sf::RectangleShape shape;
	Direction direction;
	sf::Texture texture;
	float speed;
	float size;
	//т.к. все направления на одной картинке будем указывать координаты и размеры через данную структуру
	struct Eyes{
        sf::IntRect eyesLeft;
    	sf::IntRect eyesCenter;
	    sf::IntRect eyesRight;
	    sf::IntRect eyesUp;
	    sf::IntRect eyesDown;
    }eyes;
	sf::Vector2f position;
	
public:
	Ghost(Labyrinth& labyrinth);
	virtual ~Ghost();
	void changeDirection();
	void changeOppositeDirection();
	sf::FloatRect getBoards() const;
	virtual sf::Vector2f getGhostStartPosition(Labyrinth& labyrinth)const = 0;
	void teleport();
	void refresh(float time, Labyrinth& labyrinth);
	void draw(sf::RenderWindow& window);
};

class Inky :public Ghost {
public:
	Inky(Labyrinth& labyrinth);
	virtual sf::Vector2f getGhostStartPosition(Labyrinth& labyrinth)const;
};


class Pinky :public Ghost {
public:
	Pinky(Labyrinth& labyrinth);
	virtual sf::Vector2f getGhostStartPosition(Labyrinth& labyrinth)const;
};

class Blinky :public Ghost {
public:
	Blinky(Labyrinth& labyrinth);
	virtual sf::Vector2f getGhostStartPosition(Labyrinth& labyrinth)const;
};

class Clyde :public Ghost {
public:
	Clyde(Labyrinth& labyrinth);
	virtual sf::Vector2f getGhostStartPosition(Labyrinth& labyrinth)const;
};
#endif // !_GHOST_H_
