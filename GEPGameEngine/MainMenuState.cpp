#include "MainMenuState.h"
#include "Game.h"
#include "GameState.h"

void MainMenuState::Enter()
{
	cout << "Entering MainMenu...\n";
	Game::Instance()->SetLeftMouse(false);
	bgSpriteTex = Game::Instance()->LoadTexture("backFront.png");
	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,400,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,600,400,100 }));
}

void MainMenuState::Update()
{

	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::play]->Clicked())
	{
		//we need to switch to gamestate ... 
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}

	else if (m_vButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		Game::Instance()->QuitGame();
	}

}


void MainMenuState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();
	SDL_Texture* titleSpriteTex = Game::Instance()->LoadTexture("title.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;

	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	bgDestRect.x = 240;
	bgDestRect.y = 120;
	bgDestRect.h = 200;
	bgDestRect.w = 550;
	SpriteEx* title = new SpriteEx(titleSpriteTex, bgSrcRect, bgDestRect);
	title->Render();
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	
	
	ScreenState::Render();
}

void MainMenuState::Exit()
{
	cout << "Exiting MainMenu...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}