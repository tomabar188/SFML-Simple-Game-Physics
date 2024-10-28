#include "Environment.h"

Environment::Environment( float width, float height)
    : gravity(981.0f), groundLevel(height-100) {

    groundBar.setSize(sf::Vector2f(width, 50.0f));  
    groundBar.setFillColor(sf::Color::Green);        
    groundBar.setPosition(0.0f, groundLevel + groundBar.getSize().y);


    platform.setSize(sf::Vector2f(100.0f, 20.0f)); 
    platform.setFillColor(sf::Color::Blue);         
    platform.setPosition(300.0f, groundLevel - 50); 



}

float Environment::getGravity() const {
    return gravity;
}

float Environment::getGroundLevel() const {
    return groundLevel;
}

void Environment::setGravity(float newGravity) {
    gravity = newGravity;
}

void Environment::setGroundLevel(float newGroundLevel) {
    groundLevel = newGroundLevel;
    groundBar.setPosition(0.0f, groundLevel+groundBar.getSize().y); 

}
void Environment::drawGround(sf::RenderWindow& window) {
    window.draw(groundBar);
    window.draw(platform);
}

sf::RectangleShape Environment::getPlatform() const {
    return platform;
}