#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main( int argc, char * args[])
{
    srand(time(NULL));
    SDL_Window * window(NULL);
    SDL_Surface * screenSurface(NULL);
    if(SDL_Init(SDL_INIT_VIDEO < 0))
        std :: cout << "sdl cannot init" << SDL_GetError() << std :: endl;
    else
    {
    window = SDL_CreateWindow("Test sdl ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
       if(window == NULL)
            std :: cout << "Window could not be created " << SDL_GetError();
        else
        {
            for(int i = 0; i < 20; i++)
            {
                screenSurface = SDL_GetWindowSurface(window);
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, rand()%255, rand()%255, rand()%255));
                SDL_UpdateWindowSurface(window);
                SDL_Delay(200);
            }
        }
    }
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}