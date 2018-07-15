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

class LTexture
{
    public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std :: string path);
    void free();
    void render(int x, int y, SDL_Rect * clip = NULL);
    int getWidth();
    int getHeight();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMod(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);

    private:
    SDL_Texture * mTexture;

    int mWidth;
    int mHeight;
};

LTexture gFooTexture;
LTexture gBackGroundTexture;
//SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;
LTexture gModulatedTexture;
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

LTexture :: LTexture():
mTexture(NULL),
mWidth(0),
mHeight(0)
{}
LTexture :: ~LTexture()
{
    free();
}
bool LTexture :: loadFromFile( std :: string path)
{
    free();
    SDL_Texture * newTexture(NULL);
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
        std :: cout << "Unable to load image " << IMG_GetError() << std :: endl;
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std :: cout << "Unable to create texture form file" << SDL_GetError() << std :: endl;
        else 
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
    mTexture = newTexture;
    return mTexture != NULL;
}
void LTexture :: free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void LTexture :: render( int x, int y, SDL_Rect * clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}
int LTexture :: getWidth()
{
    return mWidth;
}
int LTexture :: getHeight()
{
    return mHeight;
}
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
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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
void LTexture :: setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture :: setBlendMod(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}
void LTexture :: setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
bool loadMedia()
{
    bool success(true);
    if(!gSpriteSheetTexture.loadFromFile("foo.png"))
    {
        std :: cout << "Failed to load walking animagtion texture" << std :: endl;
        success = false;
    }
    else
    {
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 64;
        gSpriteClips[0].h = 205;
        
        gSpriteClips[1].x = 64;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 64;
        gSpriteClips[1].h = 205;

        gSpriteClips[2].x = 128;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 64;
        gSpriteClips[2].h = 205;

        gSpriteClips[3].x = 196;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 64;
        gSpriteClips[3].h = 205;
    }
    return success;
    /*bool success(true);

    if(!gModulatedTexture.loadFromFile("fadeout.png"))
    {
        std :: cout << "Failed to load front texture" << std :: endl;
        success = false;
    }
    else
    {
        gModulatedTexture.setBlendMod(SDL_BLENDMODE_BLEND);
    }
    if(!gBackGroundTexture.loadFromFile("fadein.png"))
    {
        std :: cout << "cannot load background texture" << std :: endl;
        success = false;
    }
    */
    //return success;
    /*bool success(true);
    if(!gSpriteSheetTexture.loadFromFile("dots.png"))
    {
        std :: cout << "Failed to load sprite sheet texture" << std :: endl;
        success = true;
    }
    else
    {
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 100;
        gSpriteClips[0].h = 100;

        gSpriteClips[1].x = 100;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 100;
        gSpriteClips[1].h = 100;

        gSpriteClips[2].x = 0;
        gSpriteClips[2].y = 100;
        gSpriteClips[2].w = 100;
        gSpriteClips[2].h = 100;
        
        gSpriteClips[3].x = 100;
        gSpriteClips[3].y = 100;
        gSpriteClips[3].w = 100;
        gSpriteClips[3].h = 100;
    }
    */
    /*bool success(true);
    if(!gFooTexture.loadFromFile("foo.png"))
    {
        std :: cout << "Failde to load from file " << std :: endl;
        success = false;
    }
    */
    if(!gBackGroundTexture.loadFromFile("background.png"))
    {
        std :: cout << "Failed to load image " << std :: endl;
        success = false;
    }
    return success;
    /*bool success(true);
    gTexture = loadTexture("Una.png");
    if(gTexture == NULL)
    {
        std :: cout << "Cannot load texture" << std :: endl;
        success = false;
        return success;
    }
    return success;
    */
}
void close()
{
    gFooTexture.free();
    gBackGroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
    /*SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
    */
}
SDL_Texture * loadTexture(std :: string path)
{
    SDL_Texture * newTexture(NULL);
    SDL_Surface * newSurface = IMG_Load(path.c_str());
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
    {
        std :: cout << "Cannot init sdl" << std :: endl;
    }
    else
    {
        if(!loadMedia())
            std :: cout << "Cannot load media" << std :: endl;
        else
        {
            bool quit(false);
            SDL_Event e;
            int frame(0);

            while(!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
                SDL_Rect * currentClip = &gSpriteClips[frame/4];
                gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w)/2, (SCREEN_HEIGHT - currentClip->h)/2, currentClip);

                SDL_RenderPresent(gRenderer);
                ++frame;
                if(frame/4 >= WALKING_ANIMATION_FRAMES)
                {
                    frame  = 0;
                }
            }
            /*bool quit(false);
            SDL_Event e;
            Uint8 a = 255;
            while(!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                    else if(e.type == SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym == SDLK_w)
                            a += 32;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer,0 , 0, 0, 255);
                gBackGroundTexture.render(0,0);
                gModulatedTexture.setAlpha(a);
                gModulatedTexture.render(0, 0);
                SDL_RenderPresent(gRenderer);
            }
            */
            close();
            return 0;
        }
    }
    /*Uint8 r(0), g(0), b(0);
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
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_q:
                            r += 32;
                            break;
                            
                            case SDLK_w:
                            g =+ 32;
                            break;

                            case SDLK_e:
                            b += 32;
                            break;
                        }
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
                gModulatedTexture.loadFromFile("colors.png");
                gModulatedTexture.setColor(r, g, b);
                gModulatedTexture.render(0, 0);
                SDL_RenderPresent(gRenderer);
                */
                /*SDL_RenderClear(gRenderer);
                gBackGroundTexture.render(0, 0, NULL);
                gSpriteSheetTexture.render(100,100, &gSpriteClips[0]);
                gSpriteSheetTexture.render(200, 200, &gSpriteClips[1]);
                gSpriteSheetTexture.render(300 , 300, &gSpriteClips[2]);
                gSpriteSheetTexture.render(400, 400, &gSpriteClips[3]);
                SDL_RenderPresent(gRenderer);
                */
                /*SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer),

                gBackGroundTexture.render(0,0);
                gFooTexture.render(240, 190);

                SDL_RenderPresent(gRenderer);
                */
                /*SDL_RenderClear(gRenderer);
                SDL_Rect topLeftViewPort;
                topLeftViewPort.x = 0;
                topLeftViewPort.y = 0;
                topLeftViewPort.w = SCREEN_WIDTH/2;
                topLeftViewPort.h = SCREEN_HEIGHT/2;
                SDL_Rect middleViewPort;
                middleViewPort.x = SCREEN_WIDTH/2;
                middleViewPort.y = 0;
                middleViewPort.w = SCREEN_WIDTH/2;
                middleViewPort.h = SCREEN_HEIGHT/2;
                SDL_Rect downViewPort;
                downViewPort.x = 0;
                downViewPort.y = SCREEN_HEIGHT/2;
                downViewPort.w = SCREEN_WIDTH;
                downViewPort.h = SCREEN_HEIGHT/2;
                SDL_RenderSetViewport(gRenderer, &topLeftViewPort);
                SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);
                SDL_RenderSetViewport(gRenderer, &middleViewPort);
                SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);
                SDL_RenderSetViewport(gRenderer, &downViewPort);
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
                */
            //}
        //}
    //}
    //close();
    //return 0;
}