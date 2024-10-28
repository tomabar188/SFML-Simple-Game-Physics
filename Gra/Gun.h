#pragma once
#include<SFML/Graphics.hpp>
#include "Environment.h"
#include "Bullet.h"
#include <vector>
#include <memory>

class Gun : public sf::Drawable 
{
public:
	Gun(Environment& env) : environment(env) {
		initGunParts();
		
		isEquipped = false;
		gravity = environment.getGravity();
		weight = 500.0f;
		velocityY = 0;
		groundY = environment.getGroundLevel();
		std::vector<std::unique_ptr<Bullet>> bullets;
	}

	void shoot(const sf::Vector2f& startPosition, float angle);
	void drawBullets(sf::RenderTarget& target);
	void initGunParts();
	void equipGun(bool x);
	void itemUpdate(float deltaTime);
	void move(float dx, float dy);
	void setPosition(float dx, float dy);
	void setRotation(float dx);

	std::vector<std::unique_ptr<Bullet>>& getBullets() {
		return bullets;
	}

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(gunshape, states);
	}

private:
	
	Environment& environment;
	sf::ConvexShape gunshape;
	std::vector<std::unique_ptr<Bullet>> bullets;
	bool isEquipped;
	float velocityY, velocityX;
	float gravity, groundY;
	float weight;
};

