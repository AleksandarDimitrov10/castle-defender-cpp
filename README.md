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

```text
castle-defender-cpp/
├── src/
│   ├── main.cpp
│   ├── Game.cpp / Game.h
│   ├── Grid.cpp / Grid.h
│   ├── Tower.cpp / Tower.h
│   ├── Enemy.cpp / Enemy.h
│   ├── Castle.cpp / Castle.h
│   ├── AIController.cpp / AIController.h
│   └── Types.h
├── docs/
│   └── screenshots/
├── README.md
├── .gitignore
└── LICENSE
