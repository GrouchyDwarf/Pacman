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
	const float drawingRadius;//"���������" ������(��� ������������) ������� �������
	const float mouthAngle;
	const float animationPeriod;//�������� �������� �������
	float orientation;//� ��������
	float animationStage;//������ ��������(����) �� 0 �� 1
	sf::Vector2f position;
	int counter;//������� ��� ���������,����� ����������,����� pacman ������� ������� ��������

public:
	Pacman(const Labyrinth& labyrinth);
	~Pacman();
	void refreshDirection();//��������� �����������
	unsigned int getEatenCookies() const;
	sf::FloatRect getBoards()const;
	void setPoints(sf::ConvexShape& shape, const std::vector<sf::Vector2f> & points);
	void setForm(const float animationStage);
	void teleport();
	void acceleration(Labyrinth& labyrinth);
	void releaseGhost(Labyrinth& labyrinth);
	void refresh(float time,Labyrinth& labyrinth);//��������� ������� � ����������� �� ���������� ����
	void draw(sf::RenderWindow& window);//������������� �������
};

#endif // !_PACMAN_H_