#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const Keyboard::Key controls[4] = {
	Keyboard::A,	//Player 1 up
	Keyboard::Z,	//Player 1 down
	Keyboard::Up,	//Player 2 up
	Keyboard::Down	//Player 2 down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void reset(){
	//reset paddle position
	paddles[0].setPosition(10+paddleSize.x/2, gameHeight/2);
	paddles[1].setPosition(770+paddleSize.x/2, gameHeight/2);
	//reset ball position
	ball.setPosition(395+paddleSize.x/2, gameHeight/2);
	ballVelocity = {(server ? 100.0f : -100.0f), 60.0f};

}

void Load(){
	//set size and origin of paddles
	for(auto &p : paddles){
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize/2.f);
	}
	//set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius/2, ballRadius/2);
	
	reset();
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
	
	float direction1 = 0.0f;
	if(Keyboard::isKeyPressed(controls[0]))
		direction1--;
	if(Keyboard::isKeyPressed(controls[1]))
		direction1++;
	paddles[0].move(0, direction1 * paddleSpeed * dt);
	
	float direction2 = 0.0f;
	if(Keyboard::isKeyPressed(controls[2]))
		direction2--;
	if(Keyboard::isKeyPressed(controls[3]))
		direction2++;
	paddles[1].move(0, direction2 * paddleSpeed * dt);
	ball.move(ballVelocity * dt);
	
	//check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if(by > gameHeight){
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if(by < 0){
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if(bx > gameWidth){
		//right wall
		reset();
	}
	else if(bx < 0){
		//left wall
		reset();
	}
	else if(bx < paddleSize.x && 
	by > paddles[0].getPosition().y - (paddleSize.y *0.5) &&
	by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		ballVelocity.x *= -1.1f;
		ball.move(ballVelocity * dt);
	}
	else if(bx < paddleSize.x && 
	by < paddles[1].getPosition().y + (paddleSize.y * 0.5) &&
	by > paddles[1].getPosition().y - (paddleSize.y * 0.5))
	{
		ballVelocity.x *= -1.1f;
		ball.move(ballVelocity * dt);
	}
	
	
}

void Render(RenderWindow &window){
	//draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}


int main(){
	//initialise and load
	
	RenderWindow window(VideoMode(gameWidth, gameHeight), "pong");
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