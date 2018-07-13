#/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;
SDL_Surface* animeArt = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP( "Una.bmp" );
	animeArt = SDL_LoadBMP("AnimeArt.bmp");
	if( gXOut == NULL || animeArt == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			int i = 0;
			//While application is running
			while( !quit )
			{
				std :: cout << "---------------------------------------------------------------------------------------" << std :: endl;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					std :: cout << "Handle" << std :: endl;
				}

				//Apply the image
				if(i%2)
					SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
				else
					SDL_BlitSurface(animeArt, NULL, gScreenSurface, NULL);
				i++;
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
				SDL_Delay(600);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}