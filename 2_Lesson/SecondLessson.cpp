#include <SDL2/SDL.h>
#include <iostream>
 
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    bool success(true);
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std :: cout << "SDL could not initialize" << SDL_GetError() << std :: endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std :: cout << "Window cannot be created" << SDL_GetError() << std :: endl;
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}
bool loadMedia()
{
    bool success = true;

    gHelloWorld = SDL_LoadBMP("Una.bmp");
    if(gHelloWorld == NULL)
    {
        std :: cout << "Unable to load image" << SDL_GetError() << std :: endl;
        success = false;
    }
    return success;
}
void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
int main(int argc, char ** args)
{
    if(!init())
        std :: cout << "initialization failed" << std :: endl;
    else
    {
        if(!loadMedia())
            std :: cout << "Cannot load data" << std :: endl;
        else
        {
            SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
        }
    }
    close();
    return 0;
}