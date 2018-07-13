#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture * loadTexture(std :: string path);

SDL_Window * gWindow(NULL);
SDL_Renderer * gRenderer(NULL);

bool init()
{
    bool success(true);
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std :: cout << "sdl video could not be initialized " << SDL_GetError() << std :: endl;
        success = false;
    }
    else 
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            std :: cout << "Sdl render could not be set to linear " << std :: endl;
        gWindow = SDL_CreateWindow("Render simple things", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std :: cout << "Window could not be created " << SDL_GetError() << std :: endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                std :: cout << " renderer could not be initialize " << std :: endl;
                success = false;
            }
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            int imgFlags = IMG_INIT_PNG;
            if(!IMG_Init(imgFlags) & IMG_INIT_PNG)
            {
                std :: cout << "png img could not be initialized " << IMG_GetError() << std :: endl;
                success = false;
            }
        }
        
    }
    return success;
}
bool loadMedia()
{
    bool success(true);
    
    return success;
}
void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}
SDL_Texture * loadTexture(std :: string path)
{
    SDL_Texture * newTexture(NULL);
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
        std :: cout << "Cannot load image " << IMG_GetError() << std :: endl; 
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std :: cout << "texture could not be loaded " << SDL_GetError() << std :: endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
int main(int argc, char ** argv)
{
    if(!init())
        std :: cout << "SDL could not be initialized " << std :: endl;
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
            SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
            SDL_RenderClear(gRenderer);

            SDL_Rect viewPort = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
            

            for(int i = 4; i < SCREEN_HEIGHT; i += 4)
                SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/2, i);
            SDL_RenderPresent(gRenderer);
        }
    }
    close();
    return 0;
}