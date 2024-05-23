//
//  AbstractGame.h
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master

#include <stdio.h>
#include "XCube2d.h"

class AbstractGame
{
private:
	// Main Loop
	// Handlers
	void handleMouseEvents();
	void updatePhysics();

protected:
	AbstractGame();
	virtual ~AbstractGame();

	// Pointers
	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<EventEngine> eventSystem;
	std::shared_ptr<PhysicsEngine> physics;
	std::shared_ptr<MyMenuSubsystem> menuSystem;

	// Main Loop Control
	bool running;
	bool paused;
	double gameTime;
	virtual void update() = 0;
	virtual void render() = 0;

	// Input Handlers
	virtual void handleKeyEvents() = 0;
	virtual void onLeftMouseButton();
	virtual void onRightMouseButton();

	// Define Game Controls 
	void pause() { paused = true; }
	void resume() { paused = false; }

public:
	int runMainLoop();
};