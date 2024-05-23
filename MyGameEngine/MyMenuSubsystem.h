#pragma once

// Libraries to include
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ROWS = 54
#define COLUMNS = 75
#define SPRITE_SIZE 32
#define FPS 50


class MyMenuSubsystem
{
	friend class XCube2Engine;
private:
	SDL_Window* window;
	SDL_Window* gameWindow = nullptr;
	bool gameRunning = false;
public:
	MyMenuSubsystem();
	~MyMenuSubsystem();
	void otherfunction();

	//
	void welcomeScreen();
	void startSDL(const char* title);
	void closeSDL();
	void createBackground();

	static SDL_Renderer* renderer;
	static SDL_Event playerInputEvent;
};

class GameObject :MyMenuSubsystem
{
public:
	GameObject();
	GameObject(const char* spriteFileName, int xPos, int yPos);
	void setSize(int width, int height);
	void render();
	void LoadTexture(const char* spriteFileName);
protected:
	float x = -100, y = -100;

	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
	SDL_Texture* spriteTexture = nullptr;
};