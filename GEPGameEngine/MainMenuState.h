#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include "SpriteEx.h"
using namespace std;

class MainMenuState : public ScreenState
{

private:
	SDL_Texture* bgSpriteTex; //load and store background sprite tex


	SpriteEx* bg;
	vector<Button*> m_vButtons;
	enum btn{play,exit};

public:
	MainMenuState() { }

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};