#include "stdafx.h"
#include "GConsole.h"
#include "MainMenu.h"
#include "TextPanel.h"
#include "Barrier.h"
#include "Enemy.h"
#include "Player.h"
#include "Particle.h"
#include <ctime>
#include <sstream>
#include <algorithm>
#include <functional>

GConsole console = GConsole();

/*
TODO
- create game over screen
- add randomness to enemies firing
*/

enum KEYS {
	KEY_A = 0x41,
	KEY_D = 0x44,
};

enum STATE {
	MENU,
	OPTIONS,
	GAME,
	HELP,
	GAMEOVER,
	EXIT
};

STATE vMenu();
STATE vOptions();
STATE vGame();
STATE vGameOverScreen();
bool keyDown(char key);
bool isColliding(SMALL_RECT first, SMALL_RECT second);
void loadObjects();
void addDynamicObjects();
void clearDead();
void moveParticles();
void checkCollisions();
void moveEnemies();

int tickPerSecond = 12;

int gameBorderLeft = 30;
int gameBorderRight = 37;

int scoreBarrierHit = -50;
int enemyScoreModifier = 100;
int goodScoreThreshold = 3000;
int direction = 1;
bool switchDir = false;
bool playerParticlesHitBarrier = false;

std::vector<Particle> particles;
std::vector<Barrier> barriers;
std::vector<Enemy> enemies;
Player player = Player(console.GetConsoleWidth(), console.GetConsoleHeight());
TextPanel score = TextPanel("", 1);
TextPanel lives = TextPanel("", 1);


int main()
{
	STATE currentState = MENU;
	player.Translate(53, 24);
	score.Translate(10, 3);
	lives.Translate(10, 4);

	while (currentState != EXIT) {
		switch (currentState) {
		default:
		case MENU:
			currentState = vMenu();
			break;
		case OPTIONS:
			currentState = vOptions();
			break;
		case GAME:
			currentState = vGame();
			break;
		case GAMEOVER:
			currentState = vGameOverScreen();
			break;
		case EXIT:
			currentState = EXIT;
			break;
		}
	}

    return 0;
}

STATE vMenu() {
	MainMenu menu = MainMenu(console.GetConsoleWidth(), console.GetConsoleHeight());
	console.ClearConsole();
	console.AddComponent(&menu);
	console.Draw();
	switch (menu.GetMenu().WaitForInput()) {
		case '1':
			return GAME;
		case '2':
			return HELP;
		case 'X':
			return EXIT;
		default:
			return MENU;
	}
}

STATE vOptions() { 
	//Infinite enemies
	return MENU; 
}

STATE vGameOverScreen() {
	//Space Invaders
	//Game over. You scored: x
	//Unlucky/Good score
	//Press space to go back to the menu
	TextPanel title = TextPanel("Space Invaders", 14);
	TextPanel score = TextPanel("", 0);
	TextPanel input = TextPanel("Press space to go back to the menu", 34);
	std::stringstream scoreStr;
	scoreStr << "You scored " << player.getScore();
	if (player.getScore() > goodScoreThreshold) scoreStr << " nice score!";
	else scoreStr << " unlucky, try again.";
	score.setText(scoreStr.str());

	title.Translate(50, 10);
	score.Translate(41, 11);
	input.Translate(40, 13);

	console.ClearConsole();
	console.AddComponent(&title);
	console.AddComponent(&score);
	console.AddComponent(&input);
	console.Draw();

	//Make sure the screen is not accidently skipped
	while (keyDown(VK_SPACE));
	input.GetDefaultMenu().WaitForAnyKey();

	return MENU;
}

STATE vGame() {
	std::stringstream ss;
	loadObjects();

	bool moveLeft = false, moveRight = false, actionFire = false;

	while (!keyDown(VK_RETURN)) {
		moveLeft = false;
		moveRight = false;
		actionFire = false;
		ss.str(std::string());
		ss << "Score: " << std::to_string(player.getScore());
		score.setText(ss.str(), ss.str().length());
		ss.str(std::string());
		ss << "Lives: " << std::string(player.getHitpoints(), '¤');
		lives.setText(ss.str());

		console.ClearConsole();
		console.AddComponent(&score);
		console.AddComponent(&lives);
		addDynamicObjects();
		console.Draw();
		Sleep(round(1000.0 / tickPerSecond));

		if (keyDown(KEY_D) || keyDown(VK_RIGHT)) moveRight = true;
		if (keyDown(KEY_A) || keyDown(VK_LEFT)) moveLeft = true;
		if (keyDown(VK_SPACE)) actionFire = true;
		
		moveParticles();
		moveEnemies();
		checkCollisions();
		clearDead();

		//Check player should still be alive
		if (player.getHitpoints() <= 0) return GAMEOVER;
		for (int e = 0; e < enemies.size(); e++) {
			if (isColliding(enemies.at(e).GetComponentBounds(), player.GetComponentBounds())) return GAMEOVER;
		}

		if (enemies.size() == 0) return GAMEOVER;

		//Player inputs
		if (moveRight && (player.GetComponentBounds().Right < console.GetConsoleWidth() - gameBorderRight)) player.move({ 1,0 });
		if (moveLeft && (player.GetComponentBounds().Left > gameBorderLeft)) player.move({ -1,0 });
		if (actionFire) {
			particles.push_back(Particle(player.GetComponentBounds().Left + 1, player.GetComponentBounds().Top - 1, { 0, -1 }, ENEMY));
		}

	}
	return MENU; 
}

void addDynamicObjects() {
	console.AddComponent(&player);

	for (Enemy enemy : enemies) {
		console.AddComponent(&enemy);
	}

	for (Barrier barrier : barriers) {
		console.AddComponent(&barrier);
	}

	for (Particle particle : particles) {
		console.AddComponent(&particle);
	}
}

void loadObjects() {
	int enemiesPerRow = 7;
	int barriersPerRow = 9;
	int spaceFromTop = 3;

	player = Player(console.GetConsoleWidth(), console.GetConsoleHeight());
	player.setHitpoints(3);

	particles.clear();
	enemies.clear();
	barriers.clear();
	std::srand(std::time(nullptr));

	int direction = -1;
	//Type 1 enemies
	for (int i = 1; i <= 3; i++) {
		int currentEnemy = (i-1) * enemiesPerRow;
		for (int enemy = 0; enemy < enemiesPerRow; enemy++, currentEnemy++) {
			enemies.push_back(Enemy(i, console.GetConsoleWidth(), console.GetConsoleHeight()));
			enemies.at(currentEnemy).Translate(enemy * 6 + 36, (i-1) * 4 + spaceFromTop);
		}
	}

	//Barriers
	for (int i = 0; i < barriersPerRow; i++) {
		int rand = std::rand() % 3;
		barriers.push_back(Barrier(console.GetConsoleWidth(), console.GetConsoleHeight()));
		barriers.at(i).Translate(i * 6 + 30, spaceFromTop + 17);
	}

}

bool isColliding(SMALL_RECT first, SMALL_RECT second) {
	if (second.Right <= first.Left || second.Left >= first.Right) return false;
	if (second.Bottom <= first.Top || second.Top >= first.Bottom) return false;

	return true;
}

void moveParticles() {
	//Move particles
	for (int p = 0; p < particles.size(); p++) {
		particles.at(p).move();
	}
}

void checkCollisions() {
	std::vector<int> particlesToErase;

	//barriers & enemies
	for (int e = 0; e < enemies.size(); e++) {
		for (int b = 0; b < barriers.size(); b++) {
			if (e != 0 && e != enemies.size() && isColliding(enemies.at(e).GetComponentBounds(), barriers.at(b).GetComponentBounds())) {
				enemies.at(e).hit();
				barriers.at(b).hit();

				if (enemies.at(e).getHitpoints() == 0) enemies.erase(enemies.begin() + e);
				if (barriers.at(b).getHitpoints() == 0) barriers.erase(barriers.begin() + b);
			}
		}
	}

	//particles & barriers
	for (int p = 0; p < particles.size(); p++) {
		for (int b = 0; b < (int)barriers.size(); b++) {
			if (isColliding(particles.at(p).GetComponentBounds(), barriers.at(b).GetComponentBounds())) {
				if (particles.at(p).getDamageType() == PLAYERANDBARRIER) {
					barriers.at(b).hit();
					particlesToErase.push_back(p);
				}

			}
		}
	}


	//particles & enemies
	for (int p = 0; p < particles.size(); p++) {
		for (int e = 0; e < (int)enemies.size(); e++) {
			if (isColliding(particles.at(p).GetComponentBounds(), enemies.at(e).GetComponentBounds())) {
				if (particles.at(p).getDamageType() == ENEMY) {
					enemies.at(e).hit();
					particlesToErase.push_back(p);
				}

			}
		}
	}

	//particles & players
	for (int p = 0; p < particles.size(); p++) {
		if (isColliding(particles.at(p).GetComponentBounds(), player.GetComponentBounds())) {
			if (particles.at(p).getDamageType() == PLAYERANDBARRIER) {
				player.hit();
				particlesToErase.push_back(p);
			}
			
		}
	}

	//Sort into asc then delete particles
	std::sort(particlesToErase.begin(), particlesToErase.end());
	for (int e = particlesToErase.size() -1; e >= 0; e--) {
		particles.erase(particles.begin() + particlesToErase.at(e));
	}

}

void clearDead() {
	//Clear up the dead
	for (int e = 0; e < (int)enemies.size(); e++) {
		if (enemies.at(e).getHitpoints() <= 0) {
			player.addScore(enemies.at(e).getType() * enemyScoreModifier);
			enemies.erase(enemies.begin() + e);
		}
	}

	for (int b = 0; b < (int)barriers.size(); b++) {
		if (barriers.at(b).getHitpoints() <= 0) barriers.erase(barriers.begin() + b);
	}

	for (int p = particles.size() - 1; particles.size() > 0, p >= 0; p--) {
		if (particles.at(p).GetComponentBounds().Top < 2) particles.erase(particles.begin() + p);
	}
}

void moveEnemies() {
	//Enemy movement & collision
	for (int e = 0; e < enemies.size(); e++) {
		int randMoveCount = rand() % 15 + 15;

		switch (enemies.at(e).getType()) {
		case 1:
		case 3:
			enemies.at(e).move(direction);
			break;
		case 2:
			enemies.at(e).move(direction * -1);
			//Get random between 15 & 30 for moveCounter
			if (enemies.at(e).getMoveCounter() >= randMoveCount) {
				particles.push_back(Particle(enemies.at(e).GetComponentBounds().Left + 1, enemies.at(e).GetComponentBounds().Bottom + 1, { 0, 1 }, PLAYERANDBARRIER));
				enemies.at(e).resetMoveCounter();
			}
			break;
		}

		if (enemies.at(e).GetComponentBounds().Left <= gameBorderLeft || enemies.at(e).GetComponentBounds().Right >= console.GetConsoleWidth() - gameBorderRight) {
			switchDir = true;
		}

	}

	if (switchDir) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies.at(i).move(0, 1);
		}

		switchDir = false;
		direction *= -1;
	}
}

bool keyDown(char key) {
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}