#include "player.h"
using namespace std;
using namespace sf;

void Player::update(double dt) {	
	// Movement
	sf::Vector2f direction = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction.x --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction.x ++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		direction.y --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		direction.y ++;
	}
	move((float)dt * direction * _speed);

		
	Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
		_shape->setFillColor(Color::Magenta);
		_shape->setOrigin(Vector2f(25.f, 25.f));
	}
	
void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}

