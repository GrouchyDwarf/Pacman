#include"PacMan.h"

#include<iostream>

const float PI = 3.1415926536;

Pacman::Pacman(const Labyrinth& labyrinth):radius(16),drawingRadius(13.5),mouthAngle(90),animationPeriod(0.7){
	speed = 100;
	eatenCookies = { 0,0 };
	shape.setFillColor(sf::Color::Yellow);
	position = labyrinth.getStartPosition('@');
	shape.setPosition(labyrinth.getStartPosition('@'));
	direction = Direction::STAY;
	//поворачиваем по часовой стрелке,изначально фигура прорисовывается вертикально,с ориентацией вниз,т.к. в sfml y направлен вниз,
	//а не как обычно вверх
	orientation = 270;
	animationStage = 0.25;
}

Pacman::~Pacman() {}

void Pacman::refreshDirection() {
	direction = Direction::STAY;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction = Direction::RIGHT;
		orientation = 270;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction = Direction::LEFT;
		orientation = 90;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direction = Direction::UP;
		orientation = 180;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction = Direction::DOWN;
		orientation = 0;
	}
}

void Pacman::setPoints(sf::ConvexShape& shape,const std::vector<sf::Vector2f> & points) {
	shape.setPointCount(points.size());
	for (int i = 0; i < points.size();++i) {
		shape.setPoint(i, points[i]);
	}
}

void Pacman::setForm(const float animationStage) {
	//Для отрисовки круга удобнее использовать полярную систему координат,через которую и будем считать и переводить результат в декартовые
    //(удобнее увеличивать угол,чем просчитывать каждую точку)
    //Для перевода воспользуемся такой системой:
    //x = r*cos(a);
    //y = r*sin(a);
	//Так же для этой операции не забываем перевести градусы в радианы: a*PI/180,т.к. в прошлых формулах угол хранится именно в радианах
	//фаза и угол на который будет раскрываться рот в данный момент
	const float halfStage = fabs(animationStage-0.5);
	const float halfAngle = (halfStage * mouthAngle);
	std::vector<sf::Vector2f> points;
	//т.к. в sfml система координат представлена в виде ось y смотрит не вверх как мы привыкли,а вниз мы получим перевернутую картинку
	//рисовал именно для стандартного представления(для наглядности),с помощью setRotation() это легко исправляется
	for (float i = -90.0; i <= 90 - halfAngle; i += 10.0) {
		points.push_back(drawingRadius * sf::Vector2f(cos((i * PI) / 180), sin((i * PI) / 180)));
	}
	for (float i = 270.0; i >= 90 + halfAngle;i -= 10.0) {
			points.push_back(drawingRadius * sf::Vector2f(cos((i * PI) / 180), sin((i * PI) / 180)));
	}
	setPoints(shape, points);
}

void Pacman::teleport() {
	//слева на один пискель вперед,и справа на один назад соответсвенно(чтобы не происходило зацикливание)
	if (position.x > 945 && position.y == 496) {
		position = { 13,496 };
	}
	else if (position.x < 12 && position.y == 496) {
		position = { 944, 496 };
	}
	shape.setPosition(position);
}

void Pacman::acceleration(Labyrinth& labyrinth) {//ускорение
	if (this->eatenCookies.bigCookies > counter) {
		++counter;
		speed *= 1.10;
		this->releaseGhost(labyrinth);//при ускорении выпускаем одно приведение
	}
}

void Pacman::releaseGhost(Labyrinth& labyrinth) {
	labyrinth.deleteTemporaryBarrier();
}

Cookies& operator+=(Cookies& left,const Cookies& right) {
	left.cookies += right.cookies;
	left.bigCookies += right.bigCookies;
	return left;
}

void Pacman::refresh(const float time,Labyrinth& labyrinth) {
	float move = speed * time;
	(*this).refreshDirection();
	sf::Vector2f movement(0.0, 0.0);
	switch (direction) {
	case Direction::RIGHT:
		movement.x += move;
		break;
	case Direction::LEFT:
		movement.x -= move;
		break;
	case Direction::UP:
		movement.y -= move;
		break;
	case Direction::DOWN:
		movement.y += move;
		break;
	case Direction::STAY:
		break;
	}
	//при столкновении останавливаем пакмана
	if (labyrinth.bumpBorder(this->getBoards(), movement)) {
		direction = Direction::STAY;//сам процесс остановки прописан в лабиринте
	}
	eatenCookies += labyrinth.eatCookies(this->getBoards());//увеличиваем на значение,которое съели за раз
	acceleration(labyrinth);//ускорение
	position += movement;
	shape.move(movement);
	shape.setRotation(orientation);
	teleport();
	if (direction == Direction::STAY) animationStage = 0.25;//придаем рту определенную форму,которая будет сохранена до начала движения
	else {
		//расчитываем фазу анимации
		float newAnimationStage = time / animationPeriod;
		animationStage = fmod(animationStage + newAnimationStage, 1.0);//fmod- % для вещественных чисел,чтобы фаза не выходила за 1
	}
	setForm(animationStage);
}

void Pacman::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

sf::FloatRect Pacman::getBoards() const{
	return sf::FloatRect(position.x - radius, position.y - radius, 2.0 * radius, 2.0 * radius);
}

unsigned int Pacman::getEatenCookies() const{
	return eatenCookies.bigCookies + eatenCookies.cookies;
}
