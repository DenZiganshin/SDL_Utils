#include <SDL2/SDL.h>
#include "include/utils.h"


SDL_Window *wnd;
SDL_Renderer *rend;

// -lmingw32 -lSDL2main -lSDL2 -Llib -lutils


int main(int argc, char* argv[]){
    if(!MyUtils::basicInit(wnd, rend, 300, 300))
        return 1;

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

        SDL_RenderPresent( rend );
        SDL_Delay(20);
    }

    MyUtils::basicQuit(wnd,rend);
    return 0;
}
