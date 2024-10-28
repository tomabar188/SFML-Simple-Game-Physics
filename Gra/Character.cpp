#include <cmath>
#include < math.h >
#include "Character.h"
#include "Gun.h"
#include"Display.h"

#define _USE_MATH_DEFINES
# define M_PI           3.14159265358979323846/* pi */


void Character::setPositionOnGround() {
	torso.setPosition(torso.getPosition().x, groundY - torso.getSize().y);
	updateBodyPositions();
}

sf::Vector2f Character::getPosition() {
	return torso.getPosition();
}

void Character::setPosition(float x, float y) {
	torso.setPosition(x, y);
}

void Character::move(float dx, float dy) {

	torso.move(dx, dy);
	head.move(dx, dy);
	leftArm.move(dx, dy);
	rightArm.move(dx, dy);
	leftLeg.move(dx, dy);
	rightLeg.move(dx, dy);
	

}



void Character::stopHorizontalMovement() {
	velocityX = 0.0f;
	walkCycle = 0;
	leftLeg.setRotation(0.0f);
	rightLeg.setRotation(0.0f);
	
}

void Character::moveX(float dx) {
	
	if (isCrouching) velocityX = dx / 100;
	else velocityX = dx;

	walkCycle += 0.6;
	move(dx, 0);
}


void Character::startCrouch() {
	if (!isCrouching && !isJumping) {
		torso.setPosition(torso.getPosition().x, torso.getPosition().y + 40);
		isCrouching = true;
		updateBodyPositions();
	}
	
}

void Character::stopCrouch() {	
	if (isCrouching && !isJumping) {
		torso.setPosition(torso.getPosition().x, torso.getPosition().y - 40);
		isCrouching = false;
		updateBodyPositions();
	}
	
}


void Character::startJump() {
	if (!isCrouching && !isJumping){// && getPosition().y >= groundY - torso.getSize().y) {
		isJumping = true;
		velocityY = -jumpSpeed;
	}
}

void Character::stopJump() {
	isJumping = false;
	velocityY = 0.0f;
}

void Character::update(sf::Vector2f mousePosition, float deltaTime, const Environment& environment) {
	
	updateArm(mousePosition);
	
	updateGunPosition();
	

	
	float walkAngle = sin(walkCycle) * 20; // Zasiêg - nogi +/- 20 stopni
	if (!isDead) {
		leftLeg.setRotation(walkAngle);
		rightLeg.setRotation(-walkAngle);
	}

	if (gunAttached && gun) {
		gun->itemUpdate(deltaTime);  
	}
	

	/*if (isJumping) {
		velocityY += gravity * deltaTime; // Grawitacja
		float dy = velocityY * deltaTime;
		move(0, dy);

		if (getPosition().y > groundY - torso.getSize().y) {
			setPositionOnGround();
			isJumping = false;
			velocityY = 0.0f;
		}
	}*/



	
	sf::FloatRect platformBounds = environment.getPlatform().getGlobalBounds();

	
	sf::Transform transform = torso.getTransform();
	sf::Vector2f leftFootPos = transform.transformPoint(torso.getPoint(3)); 
	sf::Vector2f rightFootPos = transform.transformPoint(torso.getPoint(2)); 

	if (isJumping) {
		velocityY += gravity * deltaTime;
		float dy = velocityY * deltaTime;
		move(0, dy);

		
		if (platformBounds.contains(leftFootPos.x, leftFootPos.y + leftLeg.getSize().y) || platformBounds.contains(rightFootPos.x, rightFootPos.y + rightLeg.getSize().y)) {
			
			torso.setPosition(torso.getPosition().x, environment.getPlatform().getPosition().y - torso.getSize().y -leftLeg.getSize().y);
			updateBodyPositions();
			//isJumping = false;
			velocityY = 0.0f;
		}
		
		if (getPosition().y + torso.getSize().y >= environment.getGroundLevel()) {
			
			setPositionOnGround();
			isJumping = false;
			velocityY = 0.0f;
		}
	
	}



	if (isDying) {
       
        velocityY += gravity * deltaTime;
        torso.move(0, velocityY * deltaTime);

        
        torso.rotate(rotationSpeed * deltaTime);
        head.rotate(rotationSpeed * deltaTime);
        leftArm.rotate(rotationSpeed * deltaTime);
        rightArm.rotate(rotationSpeed * deltaTime);
        leftLeg.rotate(rotationSpeed * deltaTime);
        rightLeg.rotate(rotationSpeed * deltaTime);

        
        if (torso.getPosition().y + torso.getSize().y >= groundY +100) {
           
            //torso.setPosition(torso.getPosition().x, groundY - torso.getSize().y);
            velocityY = 0.0f;
            rotationSpeed = 0.0f;  
            isDying = false;     
        }

        
        updateBodyPositions();
    }

}



void Character::initBodyParts(float x, float y) {
	// glowa
	head.setRadius(20);
	head.setFillColor(sf::Color::Yellow);
	head.setOrigin(20, 20);
	head.setPosition(x, y);

	// tulow
	torso.setSize(sf::Vector2f(40, 60));
	torso.setFillColor(sf::Color::Blue);
	torso.setOrigin(20, 0);
	torso.setPosition(x, y+20);

	// rece
	leftArm.setSize(sf::Vector2f(10, 50));
	leftArm.setFillColor(sf::Color::Green);
	leftArm.setOrigin(5, 0);
	leftArm.setPosition(x-20, y+30);

	rightArm.setSize(sf::Vector2f(10, 50));
	rightArm.setFillColor(sf::Color::Green);
	rightArm.setOrigin(5, 0);
	rightArm.setPosition(x+20, y+30);

	// nogi
	leftLeg.setSize(sf::Vector2f(10, 50));
	leftLeg.setFillColor(sf::Color::Magenta);
	leftLeg.setOrigin(0, 0);
	leftLeg.setPosition(x-20, y+80);

	rightLeg.setSize(sf::Vector2f(10, 50));
	rightLeg.setFillColor(sf::Color::Red);
	rightLeg.setOrigin(0, 0);
	rightLeg.setPosition(x+10, y+80);
}

void Character::updateArm(sf::Vector2f mousePosition) {
	if(isMain)
	{ 
	sf::Vector2f rightArmPosition = rightArm.getPosition();
	float dx = mousePosition.x - rightArmPosition.x;
	float dy = mousePosition.y - rightArmPosition.y;
	float angle = atan2(dy, dx) * 180 / M_PI - 90;
	rightArm.setRotation(angle);
	}
}

void Character::updateBodyPositions() {
	
	if (!isDead) {
		/*head.setPosition(head.getPosition().x, torso.getPosition().y - head.getRadius() * 1.5);
		leftArm.setPosition(leftArm.getPosition().x, torso.getPosition().y);
		rightArm.setPosition(rightArm.getPosition().x, torso.getPosition().y);
		if (!isCrouching) {
			leftLeg.setPosition(leftLeg.getPosition().x, torso.getPosition().y + torso.getSize().y);
			rightLeg.setPosition(rightLeg.getPosition().x, torso.getPosition().y + torso.getSize().y);
		}
		*/
		
		sf::Transform transform = torso.getTransform();

		
		leftArm.setPosition(transform.transformPoint(torso.getPoint(0)).x, transform.transformPoint(torso.getPoint(0)).y);
		rightArm.setPosition(transform.transformPoint(torso.getPoint(1)).x, transform.transformPoint(torso.getPoint(1)).y);
		head.setPosition(transform.transformPoint(torso.getPoint(0)).x + torso.getSize().x / 2, transform.transformPoint(torso.getPoint(1)).y - head.getRadius() * 1.5);
		if (!isCrouching) {
			leftLeg.setPosition(transform.transformPoint(torso.getPoint(3)).x, transform.transformPoint(torso.getPoint(3)).y);
			rightLeg.setPosition(transform.transformPoint(torso.getPoint(2)).x, transform.transformPoint(torso.getPoint(2)).y);
		}


	}
	else {

		 sf::Transform transform =torso.getTransform();

        
		leftArm.setPosition(transform.transformPoint(torso.getPoint(0)).x, transform.transformPoint(torso.getPoint(0)).y);
		rightArm.setPosition(transform.transformPoint(torso.getPoint(1)).x, transform.transformPoint(torso.getPoint(1)).y);
		head.setPosition(transform.transformPoint(torso.getPoint(0)).x+torso.getSize().x/2, transform.transformPoint(torso.getPoint(1)).y);
		leftLeg.setPosition(transform.transformPoint(torso.getPoint(3)).x, transform.transformPoint(torso.getPoint(3)).y);
		rightLeg.setPosition(transform.transformPoint(torso.getPoint(2)).x, transform.transformPoint(torso.getPoint(2)).y);
		
	}
}

bool Character::getGunAttached() {
	return gunAttached;
}

void Character::attachGun(bool attach) {
	gunAttached = attach; 
}

void Character::setGun(Gun* newGun) {
	gun = newGun;
}

void Character::shoot( sf::Vector2f mousePosition) {
	if (gunAttached && gun) {
		sf::Vector2f rightArmPosition = rightArm.getPosition();
		float dx = mousePosition.x - rightArmPosition.x;
		float dy = mousePosition.y - rightArmPosition.y;
		float angle = atan2(dy, dx) * 180 / M_PI - 90;

		sf::Vector2f armPosition = rightArm.getPosition();
		float armRotation = rightArm.getRotation();

		
		float armLength = rightArm.getSize().x;  
		float radians = armRotation * (M_PI / 180.0);  // stopnie -> radiany

		
		sf::Vector2f endOfArm;
		endOfArm.x = armPosition.x + armLength * cos(radians) - 50 * sin(radians);
		endOfArm.y = armPosition.y + armLength * sin(radians) + 50 * cos(radians);

		gun->shoot(endOfArm, radians+M_PI/2);
	}
}


void Character::updateGunPosition() {
	if (gunAttached && gun) {
		
		sf::Vector2f armPosition = rightArm.getPosition();
		float armRotation = rightArm.getRotation();

		
		float armLength = rightArm.getSize().x;
		float radians = armRotation * (M_PI / 180.0);  

		
		sf::Vector2f endOfArm;
		endOfArm.x = armPosition.x + armLength * cos(radians)-50 * sin(radians);
		endOfArm.y = armPosition.y + armLength * sin(radians)+50*cos(radians);

		
		gun->setPosition(endOfArm.x,endOfArm.y);
		gun->setRotation(armRotation+90);  // obrót pistoletu zgodnie z rêk¹
	}
}

void Character::checkHitByBullet(Gun& gun) {
	auto& bullets = gun.getBullets(); 

	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(), [&](const std::unique_ptr<Bullet>& bullet) {
			if (bullet->getGlobalBounds().intersects(this->getBounds())) {
				this->takeDamage(50);  
				return true;
			}
			return false;
			}),
		bullets.end()
	);
}

void Character::takeDamage(int damage) {
	hp -= damage;
	if (hp <= 0) {
		hp = 0;
		std::cout << "Character is dead!" << std::endl;
		dying();
		
	}
	else {
		std::cout << "Character HP: " << hp << std::endl;
	}
}

void Character::updateDead() {
	torso.rotate(90);
	head.rotate(90);
	leftArm.rotate(90);
	rightArm.rotate(90);
	leftLeg.rotate(90);
	rightLeg.rotate(90);

	updateBodyPositions();
}

void Character::dying() {
	isDying = true;  
	isDead = true;
	velocityY = 0.0f;  
}
