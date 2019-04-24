**Console based Space Invaders

Space Invaders game created using my own wrapper around the Windows.h library. This wrapper allows a developer to draw to the console using objects and provides a way to draw to a specific area. Objects such as the player, enemies, particles and menus have been drawn using the wrapper.

*Files provided:
Project Specific:
- SpaceInvaders.cpp - Contains game loop, state based for screens and handles collision
- MainMenu.cpp/.h - First screen the player sees
- Object.cpp/.h - Provides a base class for any object that is drawn to the screen
	- Enemy.cpp/.h - Enemy invaders with presets for different shapes and different amounts of lifepoints
	- Player.cpp/.h - Player model with lifepoints and scoring
	- Particle.cpp/.h - For spawning particles which travel in a specific direction (Player or Invader bullets)
	- Barrier.cpp/.h - Barriers between Player and Invaders. Has different models dependant on the amount of times the barrier is hit
GConsole wrapper:
- GConsole.cpp/.h - Handles the screen buffer
- ConsoleComponent.cpp/.h - Base class for any component to be drawn on screen
- InputMenu.cpp/.h - Creation of menus with response to keypress specified
- StringBuilder.cpp/.h - Provides features such as text alignment and borders
- TextPanel.cpp/.h - Simple class to draw text to the screen
- GCBStyle.cpp/.h - Used to pass styling information between functions/objects (In later revisions this was minified and placed directly in the GConsole class)
