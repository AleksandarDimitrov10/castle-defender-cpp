# Castle Defender — C++ Tower Defense Game

Castle Defender is a text-based tower-defense game written in C++. The game takes place on a 20×20 grid where the player places towers, enemies spawn from the top of the battlefield, and the castle is located at the bottom center.

The goal is to prevent enemies from reaching the castle by placing towers strategically and surviving all enemy waves.

## Project Overview

This project was developed for a Programming with C/C++ course. It uses core C++ concepts such as arrays, structs, loops, classes, object-oriented design, and simple control logic.

The game includes battlefield rendering, tower placement, enemy movement, tower attacks, scoring, game-over conditions, and an adaptive AI system that adjusts enemy difficulty based on player performance.

## Features

- Text-based 20×20 battlefield
- Castle positioned at the bottom center of the grid
- Player tower placement
- Up to 5 towers
- Enemy spawning from the top of the grid
- Basic, fast, and strong enemy types
- Enemy movement toward the castle
- Tower attack logic based on range
- Score tracking
- Castle health system
- Five enemy waves
- Win/loss game conditions
- Adaptive AI difficulty system

## Game Rules

Enemies spawn at the top of the battlefield and move toward the castle. Towers attack enemies when they enter range. If an enemy reaches the castle row, the castle loses health and the enemy is removed.

The player wins by surviving all five waves. The AI wins if the castle health reaches zero.

## Adaptive AI

The AI system controls enemy spawning, wave progression, enemy type selection, and difficulty adaptation.

After each wave, the AI can increase enemy health if the player performs well. This makes the game more challenging over time and introduces a simple adaptive difficulty mechanism.

## Project Structure

castle-defender-cpp/
- README.md
- .gitignore
- LICENSE
- src/
  - main.cpp
  - Game.cpp
  - Game.h
  - Grid.cpp
  - Grid.h
  - Tower.cpp
  - Tower.h
  - Enemy.cpp
  - Enemy.h
  - Castle.cpp
  - Castle.h
  - AIController.cpp
  - AIController.h
  - Types.h

## Main Classes

| Class / File | Purpose |
|---|---|
| `Types.h` | Stores grid constants and the `Position` struct |
| `Tower` | Represents player-placed towers and attack behavior |
| `Enemy` | Represents enemies, movement, health, and enemy types |
| `Castle` | Stores castle position and health |
| `Grid` | Handles text-based battlefield rendering |
| `AIController` | Controls enemy spawning, waves, and adaptive difficulty |
| `Game` | Coordinates the main game loop and core gameplay logic |
| `main.cpp` | Starts the game |

## How to Compile and Run

This project is written in C++ and can be compiled with a standard C++ compiler such as `g++`.

### Compile on Windows with MinGW

g++ src/*.cpp -o castle_defender.exe

Run the game:

castle_defender.exe

### Compile on macOS/Linux

g++ src/*.cpp -o castle_defender

Run the game:

./castle_defender

## My Contribution

This was an individual C++ programming project.

My contribution involved designing and implementing the full text-based tower-defense game, including the battlefield setup, tower placement system, enemy spawning, enemy movement, tower attack logic, scoring system, castle health, win/loss conditions, wave progression, and adaptive AI difficulty.

I structured the project using multiple C++ classes to separate responsibilities between the main game loop, grid rendering, enemies, towers, the castle, and AI behavior. This made the code easier to organize, test, debug, and extend.

The main technical challenges were implementing enemy movement without collisions, keeping the printed battlefield synchronized with the internal game state, making tower range detection work correctly, and designing an adaptive AI system while staying within the course requirements.

## Challenges

The main challenges were implementing enemy movement without collisions, ensuring tower range detection worked correctly, keeping the printed battlefield synchronized with the internal game state, and designing adaptive AI while staying within the course requirements.

Because towers deal limited damage per turn, I also created a controlled test scenario to demonstrate enemy deaths, score increases, wave transitions, and adaptive difficulty changes.

## Future Improvements

Possible future improvements include:

- More tower types
- More enemy types
- Improved enemy pathfinding
- AI that reacts to tower placement
- Save/load functionality
- A graphical interface

## Technologies Used

- C++
- Object-oriented programming
- Text-based grid rendering
- Game loop logic
- Adaptive AI logic
- Basic real-time strategy / tower-defense mechanics
