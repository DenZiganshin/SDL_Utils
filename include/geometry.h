#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <SDL.h>

class Rect;
class Point : public SDL_Point{
public:
	friend class Rect;
	Point();
	Point(int _x, int _y);
	Point(const Point &p);
	Point(const SDL_Point &p);
};
class Rect: public SDL_Rect{
public:
	friend class Point;
	Rect();
	Rect(int _w, int _h);
	Rect(int _x, int _y, int _w, int _h);
	Rect(const Point &sz);
	Rect(const Point &pos, const Point &sz);
	Rect(const Point &pos, int _w, int _h);
	Rect(const Rect &r);
	Rect(const SDL_Rect &r);
	Point hitTest(int x, int y);
	Point hitTest(const Point &p);
	bool hitTest(const Rect &r);
	void draw(SDL_Renderer *r, const SDL_Color *Color = NULL);
};

#endif