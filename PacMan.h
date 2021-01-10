#pragma once
#ifndef _PACMAN_H_
#define _PACMAN_H_
#include<SFML/Graphics.hpp>
#include"Labyrinth.h"

class Pacman {
private:
	sf::ConvexShape shape;
	Direction direction;
	float speed;
	Cookies eatenCookies;
	const float radius;
	const float drawingRadius;//"насто€щий" радиус(дл€ столкновений) слишком большой
	const float mouthAngle;
	const float animationPeriod;//скорость поедани€ печений
	float orientation;//в градусах
	float animationStage;//стади€ анимации(фаза) от 0 до 1
	sf::Vector2f position;
	int counter;//счетчик дл€ ускорени€,чтобы определить,когда pacman съедает большую печеньку

public:
	Pacman(const Labyrinth& labyrinth);
	~Pacman();
	void refreshDirection();//обновл€ем направление
	unsigned int getEatenCookies() const;
	sf::FloatRect getBoards()const;
	void setPoints(sf::ConvexShape& shape, const std::vector<sf::Vector2f> & points);
	void setForm(const float animationStage);
	void teleport();
	void acceleration(Labyrinth& labyrinth);
	void releaseGhost(Labyrinth& labyrinth);
	void refresh(float time,Labyrinth& labyrinth);//обновл€ем позицию в зависимости от следующего шага
	void draw(sf::RenderWindow& window);//прорисовываем ѕакмена
};

#endif // !_PACMAN_H_