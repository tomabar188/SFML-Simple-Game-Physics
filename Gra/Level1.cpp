#include "Level1.h"


Level1::Level1()
    : display(),
    environment(display.width, display.height),
    character(environment, true, 100, 100),  
    enemy(environment, false, 500, 500),      
    enemy2(environment, false, 1000, 1000),
    enemy3(environment, false, 1500, 1500),
    gun(environment)                        
{
    
    character.setGun(&gun);
}


void Level1::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::W) {
                character.startJump();
            }
            if (event.key.code == sf::Keyboard::S) {
                character.startCrouch();
            }
            if (event.key.code == sf::Keyboard::E) {
                if (!character.getGunAttached()) {
                    gun.equipGun(true);
                    character.attachGun(true);
                }
                else {
                    gun.equipGun(false);
                    character.attachGun(false);
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                character.shoot(mousePosition);
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::S) {
                character.stopCrouch();
            }
        }

}

void Level1::handleMovement(sf::RenderWindow& window, sf::Event& event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        character.moveX(-12.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        character.moveX(12.0f);
    }
    else {
        character.stopHorizontalMovement();
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        gun.move(0, -12.f);
    }
}




void Level1::update(float deltaTime, sf::Vector2f mousePosition, sf::RenderWindow& window) {
        
    
    character.update(mousePosition, deltaTime, environment);
    enemy.update(mousePosition, deltaTime, environment);
    enemy2.update(mousePosition, deltaTime, environment);
    enemy3.update(mousePosition, deltaTime, environment);
    gun.itemUpdate(deltaTime);

    
    enemy.checkHitByBullet(gun);
    enemy2.checkHitByBullet(gun);
    enemy3.checkHitByBullet(gun);
}


void Level1::render(sf::RenderWindow& window) {
    window.clear();
    environment.drawGround(window);
    window.draw(character);
    window.draw(enemy);
    window.draw(enemy2);
    window.draw(enemy3);
    window.draw(gun);
    window.display();
}