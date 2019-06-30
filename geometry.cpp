#include "geometry.h"

Point::Point(){
	x = 0;	y=0;
}
Point::Point(int _x, int _y){
	x = _x;	y = _y;
}
Point::Point(const Point &p){
	x = p.x; y = p.y;
}
Point::Point(const SDL_Point &p){
	x = p.x; y = p.y;
	}
Rect::Rect(){
	x = 0; y = 0;
	w = 0; h = 0;
}
Rect::Rect(int _w, int _h){
	x = 0; y = 0;
	w = _w; h = _h;
}
Rect::Rect(int _x, int _y, int _w, int _h){
	x = _x; y = _y;
	w = _w; h = _h;
}
Rect::Rect(const Point &sz){
	x = 0; y = 0;
	w = sz.x; h = sz.y;
}
Rect::Rect(const Point &pos, const Point &sz){
	x = pos.x; y = pos.y;
	w = sz.x; h = sz.y;
}
Rect::Rect(const Point &pos, int _w, int _h){
	x = pos.x; y = pos.y;
	w = _w; h = _h;	
}
Rect::Rect(const Rect &r){
	x = r.x; y = r.y;
	w = r.w; h = r.h;
}
Rect::Rect(const SDL_Rect &r){
	x = r.x; y = r.y;
	w = r.w; h = r.h;
}
Point Rect::hitTest(int x, int y){
	if( (this->x + this->w < x) ||
		(this->x > x) ||
		(this->y + this->h < y) ||
		(this->y > y) )
		return Point(-1,-1);
	return Point(x-this->x, y-this->y);
}
Point Rect::hitTest(const Point &p){
	return Rect::hitTest(p.x, p.y);
}
bool Rect::hitTest(const Rect &r){
	if( (this->x + this->w < r.x) ||
		(this->x > r.x+r.w) ||
		(this->y + this->h < r.y) ||
		(this->y > r.y+r.h) )
		return false;
	return true;
}
void Rect::draw(SDL_Renderer *r, const SDL_Color *c){
	if(c != NULL)
		SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
	SDL_RenderFillRect(r, this);
}