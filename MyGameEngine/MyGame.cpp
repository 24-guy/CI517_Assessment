#include "MyGame.h"

//SDL Variables
SDL_Renderer* MyGame::renderer = nullptr;

MyGame::MyGame() : AbstractGame(), numKeys(5), box{ 20, 20, 60, 60 }, box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), phy({ 0,0 }, 10, 100), phyobj2({ 0,400 }, 2000, 10)
{
    menuSystem->otherfunction();
    gfx->setVerticalSync(true);

    physics->setGravity(2, 2);

    for (int i = 0; i < numKeys; i++)
    {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame()
{

}
void MyGame::handleKeyEvents()
{
    int speed = 3;

    if (eventSystem->isPressed(Key::W))
    {
        phy.applyForceVertical(15);
    }

    if (eventSystem->isPressed(Key::S))
    {
        phy.applyForceHorizntal(-speed);
    }

    if (eventSystem->isPressed(Key::A))
    {
        phy.applyForceHorizntal(speed);
    }

    if (eventSystem->isPressed(Key::D))
    {
        phy.applyForceVertical(-speed);
    }

}

void MyGame::update()
{


    box.y = phy.getCenter().y;
    box.x = phy.getCenter().x;
    box2.x = phyobj2.getCenter().x;
    box2.y = phyobj2.getCenter().y;

    if (!phy.isColliding(phyobj2))
    {
        phy.applyGravity(physics);
    }
    for (auto key : gameKeys)
    {

        if (key->isAlive && (box.x == key->pos.x && box.y == key->pos.y))
        {
            score += 200;
            key->isAlive = false;
            numKeys--;
        }
    }



    if (numKeys == 0)
    {
        gameWon = true;
    }
}

void MyGame::render()
{

    gfx->setDrawColor(SDL_COLOR_RED);
    gfx->drawRect(box);
    gfx->setDrawColor(SDL_COLOR_GREEN);
    gfx->fillRect(box2.x, box2.y, box2.h, box2.w);
    gfx->setDrawColor(SDL_COLOR_YELLOW);
    for (auto key : gameKeys)
        if (key->isAlive)
        {
            gfx->drawCircle(key->pos, 5);

        }
}

void MyGame::renderUI() {
    gfx->setDrawColor(SDL_COLOR_AQUA);
    std::string scoreStr = std::to_string(score);


    if (gameWon)
        std::cout << "you won: " << score;
}