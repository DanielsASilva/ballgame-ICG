# ballgame
A collect-a-thon game where you roll a ball through an open world and collect medals!!! The ball has various abilities that can be used to help exploring and collecting medals. Collect 5 medals to win the game!!
![2025-04-28-015031_hyprshot](https://github.com/user-attachments/assets/7427535e-c36c-4cc0-bf15-334c455323f4)
## Compilation Instructions
Be sure you have freeGLUT instaled on your computer, and run the following command to compile the game:
```
g++ main.cpp ball.cpp level.cpp -o game -lglut -lGL -lGLU
```
## Problems Encountered
- When colliding with walls, the ball would move vertically (fixed)
- I had an idea for a charging ability, but after a few moments, glutKeyboardUpFunc() would trigger without me unpressing the button
## Future Improvements
- Keyboard controls for a game where you can move 360 degrees are pretty rough. Being able to use a gamepad to play this game would be ideal
- Add an idle spinning animation for medals, and a shrinking animation when they are collected
- Implement a lightning system
- Use textures for the obstacles, ground and ball
