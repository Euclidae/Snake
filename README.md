# SDL Snake Game

## Overview
This is a classic Snake game implemented using the SDL2 (Simple DirectMedia Layer 2) library. The game features a minimalist design with rectangles representing the snake and food, offering a retro gaming experience.

## Current Features
- Snake movement in four directions (up, down, left, right)
- Food spawning and collision detection
- Snake growth upon eating food
- Wrapping around screen edges
- Scoring System
- Self-collision detection

## Planned Features
- Menu screen

## How to Play
1. Use arrow keys to control the snake's direction
2. Guide the snake to eat the food (cyan rectangle)
3. Avoid running into the edges of the screen (currently wraps around)
4. Grow your snake as long as possible!

## Installation and Running

### Prerequisites
- SDL2 library
- C++ compiler (g++ recommended)

### Compilation
To compile the game, use the following command:

```bash
g++ -o snake snake2.cpp -lSDL2 -lSDL2_ttf
```

### Running the Game
After compilation, run the game with:

```bash
./snake
```

## Technical Details
- Written in C++
- Uses SDL2 for graphics and input handling
- Game logic includes custom collision detection and snake movement algorithms

## Development Status
This game is currently in active development. Menu system is still in development, otherwise scoring and self-collision are implemented.

## Contributing
Contributions, ideas, and feedback are welcome! Feel free to open an issue or submit a pull request.

## Helpful Resources
- [SDL2 Official Website](https://www.libsdl.org/)
- [LazyFoo's SDL Tutorials](https://lazyfoo.net/tutorials/SDL/)
- [SDL Wiki](https://wiki.libsdl.org/)

## License
This project is licensed under the MIT License:

MIT License

Copyright (c) [2024] [Euclideus]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

Happy gaming and happy coding!
