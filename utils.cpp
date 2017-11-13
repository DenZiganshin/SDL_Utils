#include "include/utils.h"

using namespace MyUtils;

MyUtils::Sprite::Sprite():curr(0),len(1),tex(NULL),delay(0),lastTime(0),flip(SDL_FLIP_NONE){}
void MyUtils::Sprite::setFlip(bool f){
    if(f)
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;
}
void MyUtils::Sprite::setTex(SDL_Texture *t,int fps){
    tex = t;
    delay = 1000/fps;

}
void MyUtils::Sprite::setAnim(const SDL_Rect &frame,int len){
    this->frame = frame;
    cframe = frame;
    this->len = len;
}
void MyUtils::Sprite::update(long dt){
    lastTime += dt;
    if(lastTime < delay){
        return;
    }
    curr++;
    lastTime = 0;
    if(curr >= len){
        curr = 0;
    }
    cframe.x = frame.x + (frame.w*curr);
}
void MyUtils::Sprite::draw(SDL_Renderer *gRenderer, SDL_Rect &drawRect){
    SDL_RenderCopyEx( gRenderer, tex, &cframe, &drawRect, 0, NULL, flip );
}


bool MyUtils::Texture::loadTex(SDL_Renderer *rend, std::string name, Uint32 colorKey){
	SDL_Surface* loadedSurface = SDL_LoadBMP( name.c_str() );
	if(loadedSurface == NULL)
		return false;
	w = loadedSurface->w;
	h = loadedSurface->h;


	SDL_SetColorKey( loadedSurface, true, colorKey ); // enable colorkey

	texture = SDL_CreateTextureFromSurface( rend, loadedSurface );
	SDL_FreeSurface( loadedSurface );
	return true;
}

MyUtils::Rect::Rect():SDL_Rect(){}
MyUtils::Rect::Rect(int _x,int _y, int _w,int _h){
	x =_x;
	y = _y;
	w = _w;
	h = _h;
}
bool MyUtils::Rect::hitTest( const SDL_Rect &r){
	return false;
}
bool MyUtils::Rect::hitTest( const Rect &r){
	return false;
}
bool MyUtils::Rect::hitTest( const SDL_Point &p){
	return hitTest(p.x, p.y);
}
bool MyUtils::Rect::hitTest( int _x, int _y){
	if( _x < x){
		return false;
	}
	if( _x > x+w){
		return false;
	}
	if( _y < y){
		return false;
	}
	if( _y > y+h){
		return false;
	}
	return true;
}


bool MyUtils::basicInit(SDL_Window *wnd, SDL_Renderer *rend, int WindowWidth, int WindowHeight){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    wnd = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN );
    if(!wnd){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    rend = SDL_CreateRenderer( wnd, -1, SDL_RENDERER_ACCELERATED );
    if(!rend){
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

void MyUtils::basicQuit(SDL_Window *wnd, SDL_Renderer *rend){
    SDL_DestroyRenderer( rend );
    SDL_DestroyWindow( wnd );
    SDL_Quit();
}