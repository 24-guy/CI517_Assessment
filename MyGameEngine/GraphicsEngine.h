//
//  GraphicsEngine.hpp
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//



#include <stdio.h>
#include <string>
#include <memory>
#include <iostream>
//code from xcube 2d
#include <SDL.h>
#include <SDL_image.h>


#include "EngineCommon.h"
#include "GameMath.h"

/* ENGINE DEFAULT SETTINGS */
static const int DEFAULT_WINDOW_WIDTH = 800;
static const int DEFAULT_WINDOW_HEIGHT = 600;

static const SDL_Color SDL_COLOR_GRAY = { 0x80, 0x80, 0x80 };
static const SDL_Color SDL_COLOR_YELLOW = { 0xFF, 0xFF, 0 };
static const SDL_Color SDL_COLOR_RED = { 0xFF, 0, 0 };
static const SDL_Color SDL_COLOR_GREEN = { 0, 0xFF, 0 };
static const SDL_Color SDL_COLOR_BLUE = { 0, 0, 0xFF };
static const SDL_Color SDL_COLOR_BLACK = { 0, 0, 0 };
static const SDL_Color SDL_COLOR_WHITE = { 0xFF, 0xFF, 0xFF };
static const SDL_Color SDL_COLOR_AQUA = { 0, 0xFF, 0xFF };
static const SDL_Color SDL_COLOR_ORANGE = { 0xFF, 0xA5, 0 };
static const SDL_Color SDL_COLOR_PINK = { 0xFF, 0xC0, 0xCB };
static const SDL_Color SDL_COLOR_PURPLE = { 0x80, 0, 0x80 };
static const SDL_Color SDL_COLOR_VIOLET = { 0xEE, 0x82, 0xEE };

inline SDL_Color getRandomColor(int minRGB, int maxRGB)
{
    SDL_Color color = { (Uint8)getRandom(minRGB, maxRGB), (Uint8)getRandom(minRGB, maxRGB), (Uint8)getRandom(minRGB, maxRGB) };
    return color;
}

struct SDL_Colorf
{
    float r, g, b, a;
};

inline SDL_Colorf toSDLColor(SDL_Color color)
{
    SDL_Colorf colorf = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
    return colorf;
}

inline SDL_Color toSDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color color = { r, g, b, a };
    return color;
}

class GraphicsEngine
{
    friend class XCube2Engine;
private:
    SDL_Window* window;
    static SDL_Renderer* renderer;
    SDL_Color drawColor;


    Uint32 fpsAverage, fpsPrevious, fpsStart, fpsEnd;

    GraphicsEngine();

public:
    ~GraphicsEngine();

    /**
    * Clears everything on the screen
    * Call this before drawing anything to screen
    */
    void clearScreen();

    /**
    * Displays everything rendered on the screen
    * Call this method after you have finished drawing
    */
    void showScreen();

    void drawRect(const SDL_Rect&);
    void drawRect(const SDL_Rect&, const SDL_Color&);

    void drawRect(SDL_Rect*, const SDL_Color&);
    void drawRect(SDL_Rect*);
    void drawRect(const int& x, const int& y, const int& w, const int& h);

    void fillRect(SDL_Rect*);
    void fillRect(const int& x, const int& y, const int& w, const int& h);

    void drawPoint(const Point2&);
    void drawLine(const Line2i&);
    void drawLine(const Point2& start, const Point2& end);
    void drawCircle(const Point2& center, const float& radius);
    void drawEllipse(const Point2& center, const float& radiusX, const float& radiusY);
    void drawTexture(SDL_Texture*, SDL_Rect* src, SDL_Rect* dst, const double& angle = 0.0, const SDL_Point* center = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTexture(SDL_Texture*, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);


    void setDrawColor(const SDL_Color&);
    void setDrawScale(const Vector2f&);    // not tested

    /**
    * @param fileName - name of the icon file
    */
    void setWindowIcon(const char* fileName);
    void setWindowSize(const int&, const int&);
    void setWindowTitle(const char* title);
    void setWindowTitle(const std::string&);
    void setFullscreen(bool);
    void setVerticalSync(bool);

    /**
    * Shows a message box with given info and title
    *
    * Note: this function will block the execution on
    * thread where it was called
    *
    * @param info - the info to be shown
    * @param title - title of the message box, may be left out
    */
    void showInfoMessageBox(const std::string& info, const std::string& title = "");

    /**
    * @return current window's dimension
    */
    Dimension2i getCurrentWindowSize();

    /**
    * @return current display mode's resolution
    *         since most displays use native (max) resolution
    *         this returns maximum available (the one you can set) window size
    */
    Dimension2i getMaximumWindowSize();

    void setFrameStart();
    void adjustFPSDelay(const Uint32&);
    Uint32 getAverageFPS();

    static SDL_Texture* createTextureFromSurface(SDL_Surface*);

};

typedef GraphicsEngine GFX;



