#include"Ghost.h"

Ghost::Ghost(Labyrinth& labyrinth){
	speed = 80;
	size = 32;
	shape.setSize({ size,size });
	if (!texture.loadFromFile("image/ghosts.png")) {
		std::cerr << "Texture error!";
		exit(1);
	}
	shape.setTexture(&texture);
	shape.setTextureRect(eyes.eyesCenter);
	direction = Direction::STAY;
}
//при столкновении рандомно меняем направление
Ghost::~Ghost(){}
void Ghost::changeDirection() {
	srand(time(NULL));
	int i = rand() % 5;
	switch (i)
	{
	case 0:
		direction = Direction::STAY;
		break;
	case 1:
		direction = Direction::RIGHT;
		break;
	case 2:
		direction = Direction::DOWN;
		break;
	case 3:
		direction = Direction::LEFT;
		break;
	case 4:
		direction = Direction::UP;
		break;
	}
}
//для столкновения приведений между собой(меняем на противоположное направление)
//если применить опять рандом они могут не мало времени мешать друг-другу
void Ghost::changeOppositeDirection() {
	switch (direction) {
	case Direction::LEFT:
		direction = Direction::RIGHT;
		break;
	case Direction::RIGHT:
		direction = Direction::LEFT;
		break;
	case Direction::UP:
		direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		direction = Direction::UP;
		break;
	}
}

void Ghost::teleport() {
	//слева на один пискель вперед,и справа на один назад соответсвенно(чтобы не происходило зацикливание)
	if (position.x == 800 && position.y == 288)
		shape.setPosition(1, 288);
	else if (position.x == 0 && position.y == 288)
		shape.setPosition(799, 288);
}
void Ghost::refresh(float time, Labyrinth& labyrinth) {
	float move = speed * time;
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
		(*this).changeDirection();
		break;
	}
	position += movement;
	if (labyrinth.bumpBorder(shape.getGlobalBounds(), movement)) {
		(*this).changeDirection();//меняем направление при столкновении со стеной
	}
	shape.move(movement);
	teleport();
	//при выборе направления еще и указываем определенную картинку для глаз
	switch (direction) {
	case Direction::RIGHT:
		shape.setTextureRect(eyes.eyesRight);
		break;
	case Direction::LEFT:
		shape.setTextureRect(eyes.eyesLeft);
		break;
	case Direction::STAY:
		shape.setTextureRect(eyes.eyesCenter);
		break;
	case Direction::UP:
		shape.setTextureRect(eyes.eyesUp);
		break;
	case Direction::DOWN:
		shape.setTextureRect(eyes.eyesDown);
		break;
	}
}

void Ghost::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

sf::FloatRect Ghost::getBoards() const{
	return (*this).shape.getGlobalBounds();
}

//INKY
Inky::Inky( Labyrinth& labyrinth):Ghost(labyrinth){
	eyes.eyesLeft = { 0,160,32,32 };
	eyes.eyesCenter = { 32,160,32,32 };
	eyes.eyesRight = { 64,160,32,32 };
	eyes.eyesUp = { 96,160,32,32 };
	eyes.eyesDown = { 128,160,32,32 };
	shape.setPosition((*this).getGhostStartPosition(labyrinth));
}
sf::Vector2f Inky::getGhostStartPosition(Labyrinth& labyrinth) const{
	return labyrinth.getStartPosition('I');
}

//PINKY
Pinky::Pinky(Labyrinth& labyrinth) :Ghost(labyrinth) {
	eyes.eyesLeft = { 0,192,32,32 };
	eyes.eyesCenter = { 32,192,32,32 };
	eyes.eyesRight = { 64,192,32,32 };
	eyes.eyesUp = { 96,192,32,32 };
	eyes.eyesDown = { 128,192,32,32 };
	shape.setPosition((*this).getGhostStartPosition(labyrinth));
	//shape.setFillColor(sf::Color(204, 78, 151));
}
sf::Vector2f Pinky::getGhostStartPosition(Labyrinth& labyrinth) const {
	return labyrinth.getStartPosition('P');
}

//BLINKY
Blinky::Blinky(Labyrinth& labyrinth) :Ghost(labyrinth) {
	eyes.eyesLeft = { 0,0,32,32 };
	eyes.eyesCenter = { 32,0,32,32 };
	eyes.eyesRight = { 64,0,32,32 };
	eyes.eyesUp = { 96,0,32,32 };
	eyes.eyesDown = { 128,0,32,32 };
	shape.setPosition((*this).getGhostStartPosition(labyrinth));
}
sf::Vector2f Blinky::getGhostStartPosition(Labyrinth& labyrinth) const {
	return labyrinth.getStartPosition('B');
}

//CLYDE
Clyde::Clyde(Labyrinth& labyrinth) :Ghost(labyrinth) {
	eyes.eyesLeft = { 0,32,32,32 };
	eyes.eyesCenter = { 32,32,32,32 };
	eyes.eyesRight = { 64,32,32,32 };
	eyes.eyesUp = { 96,32,32,32 };
	eyes.eyesDown = { 128,32,32,32 };
	shape.setPosition((*this).getGhostStartPosition(labyrinth));
}
sf::Vector2f Clyde::getGhostStartPosition(Labyrinth& labyrinth) const {
	return labyrinth.getStartPosition('C');
}

