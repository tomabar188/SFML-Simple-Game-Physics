#pragma once
#include <vector>
#include <memory>
#include<iostream>
#include"SFML/Graphics.hpp"

class Bullet : public sf::Drawable {
public:
    Bullet(const sf::Vector2f& startPosition, float angle, float speed, float lifespan)
        : position(startPosition), velocity(speed* cos(angle), speed* sin(angle)), lifespan(lifespan) {
        shape.setPosition(startPosition);
        shape.setRadius(2.0f); 
        shape.setFillColor(sf::Color::White);
    }

    void update(float deltaTime) {
        position += velocity * deltaTime;
        shape.setPosition(position);
        lifespan -= deltaTime;  // TTL naboju--
    }

    bool isExpired() const {
        return lifespan <= 0;  // TTL naboju
    }

    sf::FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape, states);
    }

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    float lifespan;
};