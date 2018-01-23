#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
using namespace std;
using namespace sf;

Texture spritesheet;
Sprite invader;
vector<Ship *> ships;

void Load(){
	if(!spritesheet.loadFromFile("res/img/invaders_sheet.png")){
		cerr << "Failed to load spritesheet" << endl;
	}

		invader.setTexture(spritesheet);
		invader.setTextureRect(sf::IntRect(0,0,32,32));
		Invader* inv = new Invader(sf::IntRect(0,0,32,32), {100,100});
		ships.push_back(inv);
}

void Update(RenderWindow &window){
	//reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while(window.pollEvent(event)){
		if(event.type == Event::Closed){
			window.close();
			return;
		}
	}
	//quit via ESC key
	if(Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();
}

void Render(RenderWindow &window){
	//draw everything
	window.draw(invader);
}


int main(){
	//initialise and load
	
	RenderWindow window(VideoMode(gameWidth, gameHeight), "space invaders");
	Load();
	
	while(window.isOpen()){
		//calculate dt Delta-Time
		window.clear();
		Update(window);
		Render(window);
		window.display();
		
	}
	
	return 0;
}