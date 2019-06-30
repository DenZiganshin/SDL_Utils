#include <SDL.h>
#include <stdio.h>
#include "texturemanager.h"
#include "geometry.h"

SDL_Window *g_wnd = NULL;
SDL_Renderer *g_rend = NULL;


bool init_sdl(SDL_Window* &wnd, SDL_Renderer* &rend, int WindowWidth, int WindowHeight){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    wnd = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN );
    if(wnd == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    rend = SDL_CreateRenderer( wnd, -1, SDL_RENDERER_ACCELERATED );
    if(rend == NULL){
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

void deinit_sdl(SDL_Window* &wnd, SDL_Renderer* &rend){
    SDL_DestroyRenderer( rend );
    SDL_DestroyWindow( wnd );
    SDL_Quit();
}

//gameplay
//menu
//settings


int main(int argc, char* argv[]){

	init_sdl(g_wnd, g_rend, 640, 480);

    SDL_Event e;
    bool exit = false;

    TextureManager::instance().setRend(g_rend);
    if(!TextureManager::instance().loadTexture("pic.bmp", "pic"))
        return -1;
		
	unsigned int lastTime = SDL_GetTicks(),currTime, dt;
	
    while(!exit){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                exit = true;
            }else if(e.type == SDL_FINGERDOWN){
				exit = true;
			}
        }
		currTime = SDL_GetTicks();
		dt = currTime - lastTime;
		//updates
		lastTime = currTime;
		//draw
        SDL_SetRenderDrawColor( g_rend, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear( g_rend );
        TextureManager::instance().drawFrame("pic", Point(0,0) );
        //draw frame point
        SDL_RenderPresent( g_rend );
        SDL_Delay(20);
    }

    deinit_sdl(g_wnd, g_rend);

    return 0;
}