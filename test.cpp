#include <SDL2/SDL.h>
#include "include/utils.h"


SDL_Window *wnd = NULL;
SDL_Renderer *rend = NULL;

// -lmingw32 -lSDL2main -lSDL2 -Llib -lutils

MyUtils::Text text;


int main(int argc, char* argv[]){

    if(!MyUtils::basicInit(wnd, rend, 300, 300)){
        return 1;
	}
	if( TTF_Init() == -1 ){
		printf( "Cannot initialize SDL_TTF! SDL_ttf Error: %s\n", TTF_GetError() );
		return 1;
	}
	if(rend == NULL){
		printf("wtf?\n");
	}
	text.loadFont("arial.ttf", 12);
	SDL_Color c = {255,0,0};
	SDL_Texture *txtHello = text.printToTex(rend, u8"Привет!", c);

    SDL_Event e;
    bool exit = false;

    while(!exit){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                exit = true;
            }
        }

        SDL_SetRenderDrawColor( rend, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear( rend );

		SDL_RenderCopyEx(rend, txtHello, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent( rend );
        SDL_Delay(20);
    }

    MyUtils::basicQuit(wnd,rend);
	TTF_Quit();
    return 0;
}
