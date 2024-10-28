#pragma once
#include <SFML/Graphics.hpp>

class Environment {
public:
    Environment(float width, float height);

    
    float getGravity() const;
    float getGroundLevel() const;

    
    void setGravity(float newGravity);
    void setGroundLevel(float newGroundLevel);

    void drawGround(sf::RenderWindow& window);
    
    sf::RectangleShape getPlatform() const;

private:
    float gravity;
    float groundLevel;
    sf::RectangleShape groundBar;
    sf::RectangleShape platform;
};