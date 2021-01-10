#pragma once
#ifndef _LABYRINTH_H_
#define _LABYRINTH_H_
#include<SFML/Graphics.hpp>
#include<vector>
const float EPS = 0.000001;
enum  Direction {
	STAY,
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum GhostName {
	INKY,
	PINKY,
	BLINKY,
	CLYDE
};
struct Cookies {
		unsigned int cookies;
		unsigned int bigCookies;
};
class Labyrinth {
private:
	enum TypeSquare{
		BARRIER,
		TEMPORARY_BARRIER,
		PASS,
		COOKIE,
		BIG_COOKIE
	};
	struct Square {
		TypeSquare type;
		sf::FloatRect border;
	};
	struct Markers{
		const char barrier_marker = '#';
		const char cookie_marker = '.';
		const char unreachable_marker = '!';
		const char bigCookie_marker = '*';
		const char temporaryBarrier_marker = '$';	
	}markers;
	struct Colors{
		const sf::Color pass_color = sf::Color(0, 0, 0);
		const sf::Color barrier_color = sf::Color(23, 8, 158);
		const sf::Color cookie_color = sf::Color(245, 191, 12);
		const sf::Color bigCookie_color = sf::Color(250, 5, 62);
		const sf::Color temporaryBarrier_color = sf::Color(255, 0, 255);
	} colors;
	struct Sizes{
		const float tileSize = 32.0;
		const float maxShift = 16.0;
		const float cookieRadius = 2.0;
		const float bigCookieRadius = 5.0;
	}sizes;
	

	std::vector<std::vector<Square>> squares;//будем строить из них лабиринт
	sf::RectangleShape passShape;
	sf::RectangleShape barrierShape;
	sf::RectangleShape temporaryBarrierShape;
	sf::CircleShape cookieShape;
	sf::CircleShape bigCookieShape;
	
	const float minCookieArea;//площадь,которую требуется покрыть для того,чтобы печенье считалось съеденым
	std::vector<std::string> FIELD{
		{"!############################!"},
	    {"!#....#.#.##.####.##.#.#....#!"},
	    {"!#.##.#...##......##...#.##.#!"},
	    {"!#.#..#.#.##.####.##.#.#..#.#!"},
	    {"!#.####................####.#!"},
	    {"!#..#...###.#.##.#.###...#..#!"},
	    {"!#......#*#...##...#*#......#!"},
	    {"!###.####.##.####.##.####.###!"},
	    {"!#..........................#!"},
	    {"!#.#.#.#####.####.#####.#.#.#!"},
	    {"!#.#.#.......#.C$.......#.#.#!"},
	    {"!#.#.#.#####.####.#####.#.#.#!"},
	    {"!#...................B......#!"},
	    {"!####.######.#..#.######.####!"},
	    {"#####.#....#.#..#.#....#.#####"},
	    {"......#.##.#.####.#.##.#......"},
	    {"#####.........@..........#####"},
	    {"!####.###.....##.....###.####!"},
	    {"!#....###.##########.###....#!"},
	    {"!#.#......................#.#!"},
	    {"!#.#..####.###..###.####..#.#!"},
	    {"!#.##.#.P$...#..#...$I.#.##.#!"},
	    {"!#.#..####...#..#...####..#.#!"},
	    {"!#....#..##.######.##..#....#!"},
	    {"!####.......#*##*#.......####!"},
	    {"!####.#####.#.##.#.#####.####!"},
	    {"!#....#...#...##...#...#....#!"},
	    {"!#.####.#.##########.#.####.#!"},
	    {"!#..........................#!"},
	    {"!############################!"}
	};
	
public:

	Labyrinth();
	~Labyrinth();
	float getRight(const sf::FloatRect& rect);
	float getBottom(const sf::FloatRect& rect);
	bool isBetween(const float x, const float min, const float max);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getStartPosition(const char symbol) const;
	unsigned int getRemainingCookies();
	Direction selectDirection(const float top, const float bottom, const float left, const float right, const float min, const float max);
	bool bumpBorder(const sf::FloatRect& oldBoards, sf::Vector2f& move);
	Cookies eatCookies(const sf::FloatRect& borders);
	void deleteTemporaryBarrier();//для повышения сложности при ускорении пакмена выпускаем приведение(удаляет первый найденый
	//(чтобы не привязываться к координатам))
};

#endif // !_LABYRINTH_H_