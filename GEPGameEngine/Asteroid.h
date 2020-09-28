#pragma once

#include "SpriteEx.h"

class Asteroid: public SpriteEx
{
private:
	float rotationSpeed;

public:
	Asteroid(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect,float rotSpeed)
		: SpriteEx(tex,srcRect,destRect)
	{
		rotationSpeed = rotSpeed;
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius =destRect.w/2;

	}


	void Update()
	{
		angle += rotationSpeed;
	}

	


};