#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#ifndef NO_TTF
	#include <SDL2/SDL_ttf.h>
#endif
#include <stdio.h>
#include <string>

namespace MyUtils{

bool basicInit(SDL_Window* &wnd, SDL_Renderer* &rend, int WindowWidth, int WindowHeight);

void basicQuit(SDL_Window* &wnd, SDL_Renderer* &rend);

/*
*	Обертка над SDL_Texture
*/
struct Texture{
    SDL_Texture *texture;
    int w,h;

    bool loadTex(SDL_Renderer *rend, std::string name, Uint32 colorKey);
};

/*
* 	расширение SDL_Rect
*/
struct Rect : public SDL_Rect {
    Rect();
    Rect(int _x,int _y, int _w,int _h);
    bool hitTest( const SDL_Rect &r);
    bool hitTest( const Rect &r);
    bool hitTest( const SDL_Point &p);
    bool hitTest( int _x, int _y);
};

/*
* 	спрайтовая анимация
*/
struct Sprite{
    SDL_Rect frame, cframe;
    int curr, len;
    SDL_Texture *tex;
    int delay,lastTime;
    SDL_RendererFlip flip;

    Sprite();
    void setFlip(bool f); // горизонтальное отражение
    void setTex(SDL_Texture *t,int fps); //текстура и количество кадров в секунду
    void setAnim(const SDL_Rect &frame,int len); // Установка первого кадра анимации и ее длины
    void update(long dt);
    void draw(SDL_Renderer *gRenderer, SDL_Rect &drawRect); //устройство вывода и положение
};

/*
* 	работа с шрифтами
*/
#ifndef NO_TTF
class Text{
	TTF_Font *font;
public:
	Text();
	bool loadFont(std::string name, int size);
	SDL_Texture* printToTex(SDL_Renderer* gRenderer, std::string text, SDL_Color c);
};
#endif
}

#endif // UTILS_H
