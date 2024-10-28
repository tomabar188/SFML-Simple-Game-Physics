#pragma once
#include "Character.h"
#include "Gun.h"
#include "Display.h"
#include "Environment.h"
#include <SFML/Graphics.hpp>

class Level1 {
public:
    Level1();  

    
    void update(float deltaTime, sf::Vector2f mousePosition, sf::RenderWindow& window);

   
    void render(sf::RenderWindow& window);

    
    void handleEvents(sf::RenderWindow& window, sf::Event& event);

    void handleMovement(sf::RenderWindow& window, sf::Event& event);

private:
    Display display;
    Environment environment;
    Character character;
    Character enemy, enemy2, enemy3;
    Gun gun;
    sf::Clock clock;
};