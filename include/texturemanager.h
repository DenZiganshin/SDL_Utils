#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SDL.h>
#include "geometry.h"

struct Texture{
	SDL_Texture* texId;
	uint16_t width, height;
	Texture():texId(NULL), width(1), height(1){

	}
};

class TextureManager{
	//Set of sdl_textures
	std::map<std::string, Texture> textures;
	SDL_Renderer *rend;
private:
	TextureManager();
	TextureManager(const TextureManager &);
public:
	static TextureManager& instance();
	void free();
	void setRend(SDL_Renderer *r);
	bool loadTexture(std::string filename, std::string textureName, SDL_Color *key = NULL, SDL_Renderer *r = NULL);
	void drawFrame(std::string name, Rect src, Rect dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string name, Point dst, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/*
	void TextureManager::clearFromTextureMap(std::string id)
	{
		textures.erase(id);
	}
	*/
};

#endif