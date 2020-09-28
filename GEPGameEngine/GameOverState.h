#pragma once

#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

class GameOverState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { exit };

public:
	GameOverState() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};