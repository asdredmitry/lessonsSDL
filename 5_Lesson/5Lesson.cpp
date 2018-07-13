#include <SDL2/SDL.h>
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Surface * loadSurface(std :: string path);

SDL_Window * gWindow(NULL);
SDL_Surface * gScreenSurface(NULL);
SDL_Surface * gStretchedSurface(NULL);

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
        gWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std :: cout << "Window could not be created" << SDL_GetError() << std :: endl;
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
    bool success(true);
    gStretchedSurface = loadSurface("Una.bmp");
    if(gStretchedSurface == NULL)
    {
        std :: cout << "Failed to load stretching image" << std :: endl;
        success = false;
    }
    return success;
}
void close()
{
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
SDL_Surface * loadSurface(std :: string path)
{
    SDL_Surface * optimizedSurface(NULL);
    SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        std :: cout << "Unable to load image " << path << " " << SDL_GetError() << std :: endl;
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
        if(optimizedSurface == NULL)
            std :: cout << "Unable to optimize image" << path << SDL_GetError() << std :: endl;
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
    return optimizedSurface;
}
int main(int argc, char ** argv)
{
    if(!init())
        std :: cout << "Failed to initialize" << std :: endl;
    else
    {
        if(!loadMedia())
            std :: cout << "Failed to load media" << std :: endl;
        else
        {
            bool quit(false);
            SDL_Event e;
            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    return 0;
}