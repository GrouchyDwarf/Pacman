#include"Labyrinth.h"
#include <cassert>
#include<iostream>
#include<cmath>

Labyrinth::Labyrinth():minCookieArea(400.0) {
	
	squares.resize(30);
	for (int i = 0; i < FIELD.size();++i) {
		squares[i].resize(30);
		for (int j = 0; j < FIELD[i].size(); ++j) {
			sf::Color color;
			TypeSquare type;
			//����� switch �� ������,��� ��� ��������� �������� � case
			if (FIELD[i][j] == markers.barrier_marker)
				type = TypeSquare::BARRIER;
			else if (FIELD[i][j] == markers.temporaryBarrier_marker)
				type = TypeSquare::TEMPORARY_BARRIER;
			else if (FIELD[i][j] == markers.bigCookie_marker) {
				type = TypeSquare::BIG_COOKIE;
			}
			else if (FIELD[i][j] == markers.cookie_marker)
				type = TypeSquare::COOKIE;
			else if (FIELD[i][j] == markers.unreachable_marker)
				type = TypeSquare::PASS;
			else type = TypeSquare::PASS;
			squares[i][j].type = type;
			squares[i][j].border.top = i * sizes.tileSize;
			squares[i][j].border.left = j * sizes.tileSize;
			squares[i][j].border.width = sizes.tileSize;
			squares[i][j].border.height = sizes.tileSize;
		}
	}
}

float Labyrinth::getRight(const sf::FloatRect& rect) {
	return (rect.width + rect.left);
}

float Labyrinth::getBottom(const sf::FloatRect& rect) {
	return (rect.height + rect.top);
}

bool Labyrinth::isBetween(const float x, const float min, const float max) {
	return (x <= max) && (x >= min);
}

void Labyrinth::draw(sf::RenderWindow& window) {
	passShape.setFillColor(colors.pass_color);
	barrierShape.setFillColor(colors.barrier_color);
	cookieShape.setFillColor(colors.cookie_color);
	bigCookieShape.setFillColor(colors.bigCookie_color);
	temporaryBarrierShape.setFillColor(colors.temporaryBarrier_color);
	passShape.setSize({ sizes.tileSize, sizes.tileSize });
	barrierShape.setSize({ sizes.tileSize,sizes.tileSize });
	cookieShape.setRadius(sizes.cookieRadius);
	bigCookieShape.setRadius(sizes.bigCookieRadius);
	temporaryBarrierShape.setSize({ sizes.tileSize,sizes.tileSize });
	for (int i = 0; i < FIELD.size(); ++i) {
		for (int j = 0; j < FIELD[i].size();++j) {
			const sf::Vector2f position = { squares[i][j].border.left,squares[i][j].border.top };
			const sf::Vector2f center = sf::Vector2f(squares[i][j].border.width / 2,squares[i][j].border.height / 2) + position;
			switch (squares[i][j].type) {
			case TypeSquare::PASS:
				passShape.setPosition(position);
				window.draw(passShape);
				break;
			case TypeSquare::BARRIER:
				barrierShape.setPosition(position);
				window.draw(barrierShape);
				break;
			case TypeSquare::TEMPORARY_BARRIER:
				temporaryBarrierShape.setPosition(position);
				window.draw(temporaryBarrierShape);
				break;
			case TypeSquare::COOKIE:
				passShape.setPosition(position);
				cookieShape.setPosition(center.x - sizes.cookieRadius, center.y - sizes.cookieRadius);
				window.draw(passShape);
				window.draw(cookieShape);
				break;
			case TypeSquare::BIG_COOKIE:
				passShape.setPosition(position);
				bigCookieShape.setPosition(center.x - sizes.bigCookieRadius, center.y - sizes.bigCookieRadius);
				window.draw(passShape);
				window.draw(bigCookieShape);
				break;
			}

		}
	}
}

Labyrinth::~Labyrinth() {
}

sf::Vector2f Labyrinth::getStartPosition(const char symbol) const{
	for (int i = 0; i < FIELD.size();++i) {
		for (int j = 0; j <FIELD[i].size();++j) {
			if (FIELD[i][j] == symbol) {
				float tmp1 = j * sizes.tileSize;
				float tmp2 = i * sizes.tileSize;
				return { tmp1, tmp2 };//�� ������(������ �������������� �����)
			}
		}
	}
}

//������� ����,�� �������� ������ ����� ������ 
sf::FloatRect moveSquare(const sf::FloatRect& square, sf::Vector2f& moving) {
	return { square.left + moving.x,square.top + moving.y,square.width,square.height };
}
//�������� ������ ������ �����������
//� ������� min � max ��������� ����� �� �������� �� ����������� � ������������ �������� ��������
//� � ������� moving �������� ������������ ����� ��������� �����������
Direction Labyrinth::selectDirection(const float top, const float bottom,const float left,const float right,const float min,const float max) {
	Direction direction = Direction::STAY;
	float moving = FIELD[0].size() * sizes.tileSize;//�����(�������������� ����������� ��������� ������������:���������� ������ � ������ �� ������ ������ �����)
	if ((*this).isBetween(top, min, max) && (top < moving)) {
		direction = Direction::UP;
		moving = top;
	}
	if ((*this).isBetween(bottom, min, max) && (bottom < moving)) {
		direction = Direction::DOWN;
		moving = bottom;
	}
	if ((*this).isBetween(left, min, max) && (left < moving)) {
		direction = Direction::LEFT;
	    moving = left;
	}
	if ((*this).isBetween(right, min, max) && right < moving) {
		direction = Direction::RIGHT;
		moving = right;
	}
	return direction;
}

unsigned int Labyrinth::getRemainingCookies() {
	unsigned int sum = 0;
	for (int i = 0; i < FIELD.size();++i) {
		for (int j = 0; j < FIELD[i].size();++j) {
			if ((TypeSquare::COOKIE == squares[i][j].type) || (TypeSquare::BIG_COOKIE == squares[i][j].type))
				++sum;
		}
	}
	return sum;
}

//��������� �� ������������
//������������ move ����� ����������,�� ������� ����� ��������� ��������,� �� ������ ����� direction,�.�. ��� ����� ����� �� ������
//����������� ������� �����������,�� � ��� �������������� ��������
bool Labyrinth::bumpBorder(const sf::FloatRect& oldBoards, sf::Vector2f& move) {
	sf::FloatRect newBorders = moveSquare(oldBoards, move);//���,��� ������ ��������� ������ ��� �������� �����������
	bool isBump = false;
	for (int i = 0; i < FIELD.size();++i) {
		for (int j = 0; j < FIELD[i].size();++j) {
			if (squares[i][j].type != TypeSquare::BARRIER && squares[i][j].type != TypeSquare::TEMPORARY_BARRIER) continue;//������������ �� ���������
			//sf::FloatRect currentBorders = squares[i][j].border;
			//�� ������,��� left � top ��� ���������� ������ �������� ���� ��������������
			//������������� �������
			if (newBorders.intersects(squares[i][j].border)) { 
				//��������� �����������
				float topMoving = this->getBottom(newBorders) - squares[i][j].border.top;//��� ������� ������ - ���� �������
				float downMoving = this->getBottom(squares[i][j].border) - newBorders.top;//��� ������� - ���� �������
				float leftMoving = this->getRight(newBorders) - squares[i][j].border.left;//������ ������� ������� - ����� �������
				float rightMoving = this->getRight(squares[i][j].border) - newBorders.left;//������ ������� ������� - ����� �������
				float maxMoving = std::max(std::fabs(move.x), std::fabs(move.y));

				Direction direction = selectDirection(topMoving, downMoving, leftMoving, rightMoving,maxMoving + EPS,sizes.maxShift);
				if (direction == Direction::STAY)
					direction = selectDirection(topMoving, downMoving, leftMoving, rightMoving, 0, sizes.maxShift);
				//������������� ������,�� ���� �� ���� ������������� �� ��������� �����������,������� ���� ���������� �����
				switch (direction) {
				case Direction::UP:
					move.y -= topMoving;
					break;
				case Direction::DOWN:
					move.y += downMoving;
					break;
				case Direction::LEFT:
					move.x -= leftMoving;
					break;
				case Direction::RIGHT:
					move.x += rightMoving;
					break;
				case Direction::STAY:
					break;
				}
				return true;//��������� � ����� ������������		    
			}
		}
	}
	return isBump;
}
//������� ������� 
Cookies Labyrinth::eatCookies(const sf::FloatRect& borders) {
	unsigned int countCookies = 0;
	unsigned int countBigCookies = 0;
	unsigned int count = 0;
	for (int i = 0; i < FIELD.size();++i) {
		for (int j = 0; j < FIELD[i].size();++j) {
			if ((squares[i][j].type != TypeSquare::BIG_COOKIE) && (squares[i][j].type != TypeSquare::COOKIE)) {//��� ������� � ���� �������
				continue;
			}
			sf::FloatRect interect;
			//������� �������
			//����� �� ������ ���������,� ������� ��������� �������
			//intersects ����� ���������� ����������� FloatRect-� ��������,�� ������� ����������� �������� ������
			/*if ((interLeft < interRight) && (interTop < interBottom))�� ����������
			{
				intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
				return true;
			}*/
			if (squares[i][j].border.intersects(borders,interect) && (interect.height* interect.width)>= minCookieArea) {
				if (squares[i][j].type == TypeSquare::COOKIE)
					++countCookies;
				if (squares[i][j].type == TypeSquare::BIG_COOKIE)
					++countBigCookies;
				squares[i][j].type = TypeSquare::PASS;
				
			}
		}
	}
	return {countCookies,countBigCookies};
}

void Labyrinth::deleteTemporaryBarrier() {
	for (int i = 0; i < FIELD.size();++i) {
		for (int j = 0; j < FIELD.size();++j) {
			if (squares[i][j].type == TypeSquare::TEMPORARY_BARRIER) {
				squares[i][j].type = TypeSquare::PASS;
				return;//����� ��������� ������ ���� ����������,�� ����� 
			}
		}
	}
}