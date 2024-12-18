# Snake Game in C

A simple terminal-based Snake game implemented in C using the `ncurses` library. The game allows the player to control the snake using arrow keys, eat food to grow, and avoid collisions with the walls and its own body. The goal is to achieve the highest score by eating food while avoiding collisions.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Game Controls](#game-controls)
- [Code Explanation](#code-explanation)
- [License](#license)

## Features
- Simple Snake game implementation in C.
- Controls using arrow keys.
- Dynamic speed adjustment as the player eats food.
- Game over when the snake collides with the wall or itself.
- Score tracking.
- Written using the `ncurses` library for terminal-based graphics.

## Requirements
- C compiler (GCC recommended).
- `ncurses` library installed on your system for terminal graphics.

### Installing `ncurses` (Ubuntu)
If you're using Ubuntu, you can install `ncurses` by running:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
