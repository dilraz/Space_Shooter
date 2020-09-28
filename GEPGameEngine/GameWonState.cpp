
#include "GameWonState.h"
#include <iostream>
#include "Game.h"
#include "MainMenuState.h"
using namespace std;

// Begin PauseState
void GameWonState::Enter()
{
	cout << "Game Won..." << endl;
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,600,200,80 }));

}

void GameWonState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();


	//else if exit was clicked, we need to go back to main menu
	if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}


}


void GameWonState::Render()
{

	//Game::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 1);
	SDL_Texture* bgSpriteTex = Game::Instance()->LoadTexture("winner.png");
	//draw background 
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;

	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	bgDestRect.x = 240;
	bgDestRect.y = 150;
	bgDestRect.h = 450;
	bgDestRect.w = 550;
	SpriteEx* bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	bg->Render();
	ScreenState::Render();

}


void GameWonState::Exit()
{

	cout << "Exiting Game Won..." << endl;

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

