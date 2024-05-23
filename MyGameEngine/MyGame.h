#pragma once
//
//  MyGame.h
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

// Libraries
#include <stdio.h>
#include "AbstractGame.h"
#include "MyMenuSubsystem.h"

struct GameKey
{
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame
{
private:
	SDL_Rect box, box2;
	PhysicsObject phy, phyobj2;

	std::vector<std::shared_ptr<GameKey>> gameKeys;

	// Gameplay
	int numKeys, score, lives;
	bool gameWon;
	void handleKeyEvents();
	void update();
	void render();
	void renderUI();

public:
	MyGame();
	~MyGame();

	// Variables
	static SDL_Renderer* renderer;
};