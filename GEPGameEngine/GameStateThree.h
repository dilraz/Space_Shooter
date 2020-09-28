#pragma once
#include "Player.h"
#include "Asteroid.h"
#include "SDL_mixer.h"
#include "ScreenState.h"
#include "Life.h"
#include "Point.h"
#include <iostream>
using namespace std;

class GameStateThree : public ScreenState
{
private:
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex
	SDL_Texture* lifeSpriteTex;
	SDL_Texture* doubleSpriteTex;


	SpriteEx* bg;

	Player* player;
	vector<Asteroid*> asteroids;
	vector<Life*> lifes;
	vector<Point*> points;

	Mix_Chunk* fireSound;
	Mix_Chunk* engineSound;
	double a;
	double b;
	int gone;
	int lives = 3;
	int score = 0;


public:
	GameStateThree(int l, int s) { lives = l; score = s; }
	~GameStateThree() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}

	void CheckCollision();
};
