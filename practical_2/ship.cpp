#include "ship.h"
using namespace sf;
using namespace std;

Ship::Ship(){};

Ship::Ship(IntRect ir) : Sprite(){
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt){}
//define the ship destructor
Ship::~Ship() = default;
