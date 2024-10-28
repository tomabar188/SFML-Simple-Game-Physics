#include<iostream>
#include<SFML/Graphics.hpp>
#include"Character.h"
#include"Display.h"
#include"Environment.h"
#include"Gun.h"
#include "Level1.h"
using namespace sf;
using namespace std;



int main() {
	

	
	Display display;
	//Environment environment;
	//Character character(environment,true, 100, 100);
	//Character zlol(environment,false, 500, 500);

	//Gun gun(environment);
	
	

	Clock clock;
	RenderWindow window(VideoMode(display.width, display.height), "game");
	window.setFramerateLimit(60);
	
	
	Event event;
	Level1 level1;


	while (window.isOpen())
	{
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			level1.handleEvents(window, event);
		}
		
		level1.handleMovement(window, event);




		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		float deltaTime = clock.restart().asSeconds();
		
		

		level1.update(deltaTime, worldPos, window);

		
		level1.render(window);
		
		
	}



	return 0;


}