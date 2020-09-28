#pragma once

#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

class GameWonState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { exit };

public:
	GameWonState() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};