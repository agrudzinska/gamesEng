#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "player.h"
using namespace sf;
using namespace std;


Player* player;
vector<Entity *> entities;

void Reset(){
	
}

void Load() {

	player = new Player();
	entities.push_back(player);


	Reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	
	for (auto &e : entities) {
		e->update(dt);
	}
}

void Render(RenderWindow &window) {
	for (auto &e : entities) {
		e->render(window);
	}
}

int main() {
	RenderWindow window(VideoMode(800, 600), "Tile game");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}