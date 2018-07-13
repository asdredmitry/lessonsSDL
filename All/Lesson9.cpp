#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();
bool loadMedia();
void close();

SDL_Texture * loadTexture(std :: string path);

SDL_Window * gWindow(NULL);
SDL_Texture * gTexture(NULL);
SDL_Renderer * gRenderer(NULL);

bool init()
{
    bool success(true);
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std :: cout << "Initialization failed " << SDL_GetError() << std :: endl;
        success = false; 
        return success;
    }
    gWindow = SDL_CreateWindow("TestRender",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        std :: cout << "Window could not be crated " << SDL_GetError() << std :: endl;
        success = false;
        return success;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL)
    {
        std :: cout << "Renderer coudl not be created " << SDL_GetError() << std :: endl;
        success = false;
        return success;
    }
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & IMG_INIT_PNG))
    {
        std :: cout << "Img could not be initialize " << IMG_GetError() << std :: endl;
        success = false;
        return success;
    }
    return success;
}
bool loadMedia()
{
    bool success(true);
    gTexture = loadTexture("media.png");
    if(gTexture == NULL)
    {
        std :: cout << "Cannot load texture" << std :: endl;
        success = false;
        return success;
    }
    return success;
}
void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
SDL_Texture * loadTexture(std :: string path)
{
    SDL_Texture * newTexture(NULL);
    SDL_Surface * newSurface = IMG_Load("media.png");
    if(newSurface == NULL)
    {
        std :: cout << "media file could not be loaded " << IMG_GetError() << std :: endl;
        return newTexture;
    }
    newTexture = SDL_CreateTextureFromSurface(gRenderer,newSurface);
    return newTexture;
}
int main(int argc, char ** argv)
{
    if(!init())
        std :: cout << "Cannot init SDL " << std :: endl;
    else
    {
        if(!loadMedia())
            std :: cout << "Cannot load media" << std :: endl;
        else
        {
            bool quit(false);
            SDL_Event e;
            while(!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
                SDL_RenderClear(gRenderer);
                SDL_Rect topLeftViewPort;
                topLeftViewPort.x = 0;
                topLeftViewPort.y = 0;
                topLeftViewPort.w = SCREEN_WIDTH/2;
                topLeftViewPort.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer, &topLeftViewPort);
                SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}