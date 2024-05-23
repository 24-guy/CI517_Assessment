#include "MyMenuSubsystem.h"
#include <iostream>
#include "MyGame.h"


// Fonts
TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
SDL_Color textColour = { 255, 255, 200 };
SDL_Surface* textSurface = nullptr;
SDL_Texture* textTexture = nullptr;


// SDL Variables
SDL_Renderer* MyMenuSubsystem::renderer = nullptr;;
SDL_Event MyMenuSubsystem::playerInputEvent;

//object
GameObject* backGround = nullptr;

MyMenuSubsystem::MyMenuSubsystem()
{
	//
}

MyMenuSubsystem::~MyMenuSubsystem()
{
	// Debug
#ifdef __DEBUG
	debug("MyMenuSubsystem::~MyMenuSubsystem() started");
#endif
}

void MyMenuSubsystem::otherfunction()
{
	std::cout << "Other Function Called\n";
}

//

void MyMenuSubsystem::startSDL(const char* title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "\nSDL Initialised  \n";
		gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (gameWindow) printf("\nGame Window Created ");
		renderer = SDL_CreateRenderer(gameWindow, -1, 0);
		if (renderer) printf("\nRenderer Created \n");
		gameRunning = true;

		TTF_Init();
		font = TTF_OpenFont("assets/fonts/arial.ttf", 22);
		font2 = TTF_OpenFont("assets/fonts/bubble_pixel-7_dark.ttf", 18);
	}
	else
	{
		gameRunning = false;
	}
}

void MyMenuSubsystem::createBackground()
{
	backGround = new GameObject("assets/images/BG_Image.png", 0, 0);
	backGround->setSize(800, 600);
}

void MyMenuSubsystem::welcomeScreen()
{
	GameObject* splashScreen;
	splashScreen = new GameObject("assets/images/Start_Screen.png", 0, 0);
	splashScreen->setSize(800, 600);
	splashScreen->render();
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);

	std::string screenText;
	textColour = { 155,185,235 };
	SDL_Rect textRect = { 100,150,0,0 };

	screenText = "CI517 Game Engine Fundamentals";
	screenText += "\n";
	screenText += "\nPress any Key to continue";

	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	bool exitLoop = false;
	while (!exitLoop)
	{
		SDL_PollEvent(&playerInputEvent);
		if (playerInputEvent.type == SDL_MOUSEBUTTONDOWN || playerInputEvent.type == SDL_KEYDOWN)
		{
			exitLoop = true;
			std::cout << "\n\n\nJAY_GRAY_CI517-2023-24\n\n\n";
		}
	}
}
//
GameObject::GameObject()
{
	// Default
}

GameObject::GameObject(const char* spriteFileName, int xPos, int yPos)
{
	LoadTexture(spriteFileName);
	x = xPos, y = yPos;
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x; destRect.y = (int)y;
}

void GameObject::setSize(int width, int height)
{
	srcRect.w = width;
	srcRect.h = height;

	destRect.w = width;
	destRect.h = height;
}

void GameObject::render()
{
	SDL_RenderCopy(MyMenuSubsystem::renderer, spriteTexture, &srcRect, &destRect);
}

void GameObject::LoadTexture(const char* spriteFileName)
{
	SDL_Surface* tempSurface = IMG_Load(spriteFileName);
	spriteTexture = SDL_CreateTextureFromSurface(MyMenuSubsystem::renderer, tempSurface);
	if (spriteTexture == NULL)
	{
		std::cout << "\n\nImage Load Error - SDL Error %s\n\n" << SDL_GetError();
		SDL_FreeSurface(tempSurface);
	}
}

void MyMenuSubsystem::closeSDL()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_Quit();
	SDL_Quit();
	std::cout << "\nSDL Closed \n";
}