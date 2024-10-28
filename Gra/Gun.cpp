#include "Gun.h"
#include<iostream>


void Gun::initGunParts() {

	gunshape.setPointCount(6);
	gunshape.setPoint(0, sf::Vector2f(30.f, 30.f));
	gunshape.setPoint(1, sf::Vector2f(60.f, 30.f));
	gunshape.setPoint(2, sf::Vector2f(60.f, 35.f));
	gunshape.setPoint(3, sf::Vector2f(21.f, 35.f));
	gunshape.setPoint(4, sf::Vector2f(30.f, 45.f));
	gunshape.setPoint(5, sf::Vector2f(20.f, 45.f));

	gunshape.setOrigin(sf::Vector2f(30.f, 30.f));
	gunshape.setFillColor(sf::Color::Red);
	gunshape.setPosition(50, 50);
}


void Gun::itemUpdate(float deltaTime) {

	if(!isEquipped) {
		velocityY += gravity * deltaTime;
		float dy = velocityY * deltaTime;
		gunshape.move(0, dy);

		if(gunshape.getPosition().y >= groundY) {
			gunshape.setPosition(gunshape.getPosition().x, groundY);
			velocityY = -velocityY / 2;
		}
	}
	for(auto& bullet : bullets) {
		bullet->update(deltaTime);
	}
	
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), 
		[](const auto& bullet) { return bullet->isExpired(); }), bullets.end());
	
}

void Gun::shoot( const sf::Vector2f& startPosition, float angle ) {
	float bulletSpeed = 500.0f; 
	float bulletLifespan = 5.0f;  
	bullets.emplace_back(std::make_unique<Bullet>(startPosition, angle, bulletSpeed, bulletLifespan));
	std::cout << "d";
}

void Gun::drawBullets(sf::RenderTarget& target) {
	
	for (const auto& bullet : bullets) {
		target.draw(*bullet);
		std::cout << "a";
	}

}

void Gun::equipGun(bool x) {

	isEquipped=x;

}
void Gun::move(float dx,float dy) {

	gunshape.move(dx, dy);

}

void Gun::setPosition(float dx, float dy) {

	gunshape.setPosition(dx, dy);

}

void Gun::setRotation(float dx) {

	gunshape.setRotation(dx);

}
