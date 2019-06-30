#include "texturemanager.h"
#include <iostream>

//private
TextureManager::TextureManager():
	rend(NULL)
{
}
TextureManager::TextureManager(const TextureManager &){

}

//public
TextureManager& TextureManager::instance(){
	static TextureManager self;
	return self;
}
void TextureManager::free(){
}
void TextureManager::setRend(SDL_Renderer *r){
	this->rend = r;
}
bool TextureManager::loadTexture(std::string filename, std::string textureName, SDL_Color *key, SDL_Renderer *r){
	SDL_Surface *surf = SDL_LoadBMP(filename.c_str());
	if(surf == NULL){
		std::cout<<"load file failed:"<<SDL_GetError()<<std::endl;
		return false;
	}

	if(key!=NULL)
		SDL_SetColorKey(surf,SDL_TRUE, SDL_MapRGB(surf->format,key->r,key->g,key->b));

	SDL_Renderer *rnd = NULL;
	if(r != NULL){
		rnd = r;
	}
	if(rnd == NULL){
		rnd = this->rend;
	}
	if(rnd == NULL){
		std::cout<<"no SDL_Renderer found"<<std::endl;
		return false;
	}
	SDL_Texture *tId = SDL_CreateTextureFromSurface(rnd, surf);
	if(tId == NULL){
		std::cout<<"create texture failed:"<<SDL_GetError()<<std::endl;
		return false;
	}

	Texture t;
	t.width = surf->w;
	t.height = surf->h;
	t.texId = tId;
	textures[textureName] = t;
	return true;
}

void TextureManager::drawFrame(std::string name, Rect src, Rect dst, SDL_RendererFlip flip){
	if(rend == NULL)
		return;
	SDL_RenderCopyEx(this->rend, textures[name].texId, &src, &dst, 0, NULL, flip);
}

void TextureManager::drawFrame(std::string name, Point dst, SDL_RendererFlip flip){
	if(rend == NULL)
		return;
	Texture *t = &textures[name];
	Rect rsrc(0,0, t->width, t->height),
		 rdst(dst, t->width, t->height);

	SDL_RenderCopyEx(this->rend, t->texId, &rsrc, &rdst, 0, NULL, flip);
}