#pragma once

#include "SpriteEx.h"

class Life: public SpriteEx
{
private:
	float rotationSpeed;

public:
	Life(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed)
		: SpriteEx(tex, srcRect, destRect)
	{
		rotationSpeed = rotSpeed;
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius = 33;

	}


	void Update()
	{
		angle += rotationSpeed;
	}


};