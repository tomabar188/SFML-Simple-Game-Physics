#pragma once
#include<SFML/Graphics.hpp>
#include "Environment.h"
#include "Gun.h"


class Character : public sf::Drawable {
public:
    Character(Environment& env, bool main, float x, float y) : gun(nullptr), gunAttached(false), environment(env), hp(100) {

        initBodyParts(x, y);
        walkCycle = 0.0;
        rotationSpeed = 190.0f;
        velocityY = 0.0f;
        velocityX = 0.0f;
        isCrouching = false;
        jumpSpeed = 500.0f;
        gunAttached = false;
        gravity = environment.getGravity();
        isDying = false;
        isDead = false;
        isMain = main;
        groundY = environment.getGroundLevel();//torso.getPosition().y + torso.getSize().y;
        setPositionOnGround();
       
    }

    
    void stopHorizontalMovement();
    void moveX(float dx);
    void startCrouch();
    void stopCrouch();

    void startJump();
    void stopJump();
    
    void setPositionOnGround();
    void updateBodyPositions();
    void updateArm(sf::Vector2f mousePosition);
    void initBodyParts(float x, float y);
    void move(float dx, float dy);

    void update(sf::Vector2f mousePosition, float deltaTime, const Environment& environment);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();

    void setGun(Gun* newGun);
    void attachGun(bool attach);
    void shoot( sf::Vector2f mousePosition);
    void updateGunPosition();
    bool getGunAttached();

    void checkHitByBullet(Gun& gun);
    void takeDamage(int damage);
    sf::FloatRect getBounds() const {
        return torso.getGlobalBounds(); 
    }
    void dying();
    void updateDead();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(head, states);
        target.draw(torso, states);
        target.draw(leftArm, states);
        target.draw(rightArm, states);
        target.draw(leftLeg, states);
        target.draw(rightLeg, states);
        if (gunAttached && gun) {
            gun->drawBullets(target); 
        }
    }

private:
    
    Environment& environment;
    sf::CircleShape head;
    sf::RectangleShape torso, leftArm, rightArm, leftLeg, rightLeg;
    float walkCycle;    
    bool isMain, isJumping, isCrouching, isDying, isDead;
    float velocityY, velocityX;
    float rotationSpeed;
    float gravity, groundY;
    float jumpSpeed;
    Gun* gun;
    bool gunAttached;
    int hp;
};



