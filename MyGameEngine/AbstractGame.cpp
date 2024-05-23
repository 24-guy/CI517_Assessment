
//
//  AbstractGame.cpp
//  GameEngineBase
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "AbstractGame.h"
#include <iostream>
using namespace std;


AbstractGame::AbstractGame() : running(true), gameTime(0.0)
{
	cout << "Abstract Game Started" << endl;
	std::shared_ptr<XCube2Engine> engine = XCube2Engine::getInstance();

	gfx = engine->getGraphicsEngine();
	eventSystem = engine->getEventEngine();
	physics = engine->getPhysicsEngine();

	menuSystem = engine->getMyMenuSubsystem();
}

AbstractGame::~AbstractGame()
{
	cout << "Abstract Game Ended" << endl;

	gfx.reset();
	eventSystem.reset();
	physics.reset();
	menuSystem.reset();

	XCube2Engine::quit();

#ifdef __DEBUG
	debug("AbstractGame::~AbstractGame() finished");
	debug("The game finished and cleaned up successfully. Press Enter to exit");
	getchar();
#endif

}

void AbstractGame::updatePhysics()
{
	physics->update();
}

int AbstractGame::runMainLoop()
{
#ifdef __DEBUG
	debug("Entered Main Loop");
#endif

	gfx->clearScreen();
	render();
	while (running)
	{
		gfx->setFrameStart();
		eventSystem->pollEvents();
		if (eventSystem->isPressed(Key::ESC) || eventSystem->isPressed(Key::QUIT))
			running = false;

		handleKeyEvents();
		handleMouseEvents();

		if (!paused)
		{
			update();
			gameTime += 0.016; // 60 Times a Second
		}

		gfx->clearScreen();
		render();
		gfx->showScreen();

		gfx->adjustFPSDelay(16); // HardCoded to 60fps
	}

#ifdef __DEBUG
	debug("Exited Main Loop");
#endif

	return 0;
}

void AbstractGame::handleMouseEvents()
{
	if (eventSystem->isPressed(Mouse::BTN_LEFT)) onLeftMouseButton();
	if (eventSystem->isPressed(Mouse::BTN_RIGHT)) onRightMouseButton();
}

void AbstractGame::onLeftMouseButton(){}
void AbstractGame::onRightMouseButton(){}