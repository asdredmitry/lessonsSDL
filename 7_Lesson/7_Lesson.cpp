#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();

bool loadMedia();

void close();

SDL_Texture * loadTexture(std :: string path);

SDL_Window * gWindow(NULL);
SDL_Renderer * gRenderer(NULL);
SDL_Texture * gTexture(NULL);

bool init()
{
    bool success(true);
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std :: cout << "SDL could not initialize " << SDL_GetError() << std :: endl;
        success = false;
    }
    else 
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            std :: cout << "Linear texture filtering not enabled" << std :: endl;
        gWindow = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std :: cout << "Window could not be created" << SDL_GetError() << std :: endl;
            success = false;
        }
        else 
        {
            //create render for window 
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                std :: cout << "Renderer could not be created" << SDL_GetError() << std :: endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 150, 0 ,0 , 255);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)  & imgFlags))
                {
                    std :: cout << "SDL_image could not initialize " << SDL_GetError() << std :: endl;
                    success = false;
                }
            }
        }
    }
    return success;
}
bool loadMedia()
{
    bool success = true;

    gTexture = loadTexture("Una.png");
    if(gTexture == NULL)
    {
        std :: cout << "Failed to load texture image" << std :: endl;
        success = false;
    }
    return success;
}
void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}
SDL_Texture* loadTexture( std :: string path)
{
    SDL_Texture* newTexture(NULL);
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
        std :: cout << "Unable to load image " << path.c_str() << IMG_GetError() << std :: endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std :: cout << "Unable to create texture " << path.c_str() << SDL_GetError() << std :: endl;
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
    return newTexture;
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
                SDL_RenderClear(gRenderer);
                //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}