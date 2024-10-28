# SFML Game Project
This project is an early version of a C++ game using the SFML library. The player controls a character that can jump, crouch, walk, and shoot. The game includes an environment with gravity, platforms, and enemy characters.  

## Features
* Character Movement: Walk, jump, crouch, and interact with weapons.
* Physics and Environment: Simulated gravity and platform collision.
* Shooting Mechanics: Bullets with a lifespan and collision detection.
* Enemies: Multiple enemies with health and damage mechanics.
  
## Project Structure 
### Core Files

### 1. main.cpp:
Initializes the game window.
Runs the game loop, handling events, updates, and rendering.
Manages frame rate and window settings.
### 2. Environment Management
Environment.h & Environment.cpp: Manages the game’s environment, including gravity, ground level, and platform settings.

### 3. Character and Movement
Character.h & Character.cpp: Contains character actions such as movement, jumping, crouching, and interaction with weapons. Handles character health and damage.

### 4. Bullet Mechanics
Bullet.h: Defines the bullet’s properties, including its position, velocity, lifespan, and collision bounds.

### 5. Weapon System
Gun.h & Gun.cpp: Defines the gun’s behavior, including shooting bullets and managing bullet trajectories and collisions.

### 6. Level Design
Level1.h & Level1.cpp: Contains the initial game level with defined characters, enemies, and environmental settings. Manages player and enemy interactions.

### 7. Display
Display.h: Manages game display dimensions.

![2024-10-28 11 30 55](https://github.com/user-attachments/assets/84fe7e9b-7571-49d7-8e78-2e69bfa25ab3)
