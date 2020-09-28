#include "GameState.h"
#include "Game.h"
#include "PauseMenuPopupState.h"
#include "GameOverState.h"
#include "GameWonState.h"
#include "GameStateTwo.h"


void GameState::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	mainSpriteTex = Game::Instance()->LoadTexture("Sprites.png");
	lifeSpriteTex = Game::Instance()->LoadTexture("life.png");
	doubleSpriteTex = Game::Instance()->LoadTexture("double.png");
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	
	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);


	SDL_Rect asteroidSrcRect;
	asteroidSrcRect.x = 124;
	asteroidSrcRect.y = 0;
	asteroidSrcRect.w = asteroidSrcRect.h = 66;//66 pixelsx66 pixels is each cell's dimension

	
	
	for (int i = 0; i < 4; i++)
	{
		SDL_Rect asteroidDestRect;
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);
		
		asteroidDestRect.x = (rand() % 700) + 25; //generate between 25 and 700
		asteroidDestRect.y = (rand() % 400) + 100;//generate between 100 and 400
		asteroidDestRect.w = asteroidDestRect.h = (rand() % 100) + 35;
		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, r);
		asteroids.push_back(ast);
	}


	//for Lives
	SDL_Rect lifeSrcRect;
	lifeSrcRect.x = 0;
	lifeSrcRect.y = 0;
	lifeSrcRect.w = lifeSrcRect.h = 66;//66 pixelsx66 pixels is each cell's dimension

	SDL_Rect lifeDestRect;
	lifeDestRect.w = lifeDestRect.h = 66;

	for (int i = 0; i < 2; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);

		lifeDestRect.x = (rand() % 700) + 25; //generate between 1 and 700
		lifeDestRect.y = (rand() % 400) + 100;//generate between 1 and 600

		Life* life = new Life(lifeSpriteTex, lifeSrcRect, lifeDestRect, r);
		lifes.push_back(life);
	}

	//for points
	SDL_Rect pointSrcRect;
	pointSrcRect.x = 0;
	pointSrcRect.y = 0;
	pointSrcRect.w = pointSrcRect.h = 66;//66 pixelsx66 pixels is each cell's dimension

	SDL_Rect pointDestRect;
	pointDestRect.w = pointDestRect.h = 66;

	for (int i = 0; i < 2; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);

		pointDestRect.x = (rand() % 700) + 25; //generate between 1 and 700
		pointDestRect.y = (rand() % 400) + 100;//generate between 1 and 600

		Point* point = new Point(doubleSpriteTex, pointSrcRect, pointDestRect, r);
		points.push_back(point);
	}

	player = new Player(mainSpriteTex, bgDestRect.w*0.5, bgDestRect.h-100);
	a = bgDestRect.w * 0.5;
	b = bgDestRect.h - 100;
	fireSound = Mix_LoadWAV("Fire.wav");
	engineSound = Mix_LoadWAV("Engines.wav");
	Mix_VolumeChunk(fireSound, 50);
	Mix_VolumeChunk(engineSound, 50);

}


void GameState::Update()
{
	if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		Game::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update();

	for (int i = 0; i < lifes.size(); i++)
		lifes[i]->Update();

	for (int i = 0; i < points.size(); i++)
		points[i]->Update();

	if (player) this->CheckCollision();

	if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		//to do:: launch a missile...
		Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
		player->SpawnBullet();
	}
	//Play engine sound....
	if (Game::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		if (!Mix_Playing(15)) //if channel 15 is not playing
			Mix_PlayChannel(15, engineSound, -1);   //-1 because we want to loop the sound...

	}
	if (Game::Instance()->KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250); //250 is in milliseconds.. the time over which the audio will fade out...
			player->SetIdle();

		}

	}




}


void GameState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Render();

	for (int i = 0; i < lifes.size(); i++)
		lifes[i]->Render();

	for (int i = 0; i < points.size(); i++)
		points[i]->Render();

	string s = "Score: " + to_string(score);
	string l = "Lives: " + to_string(lives);
	string le = "Level: 1";
	RenderFont(true, s.c_str(), 32, 50);
	RenderFont(true, l.c_str(), 282, 50);
	RenderFont(true, le.c_str(), 750, 50);
	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 
	this->~GameState();
}

void GameState::CheckCollision()
{
	//check for the player and asteroid collision
	for (int i = 0; i < (int)asteroids.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			asteroids[i]->GetX(), asteroids[i]->GetY(),
			player->GetRadius(), asteroids[i]->GetRadius()
		))
		{
			if (lives > 0) {
				lives--;
				player->ResetPlayer(a, b);
				Mix_FadeOutChannel(15, 350);
				//there was a player-asteroid collision!!!
				cout << "Player collided with an asteroid and got killed!!\n";
				if (lives <= 0) {
					string g = "Game Over!";
					RenderFont(true, g.c_str(), 500, 50);
					Game::Instance()->GetFSM()->PushState(new GameOverState());
					return; //to make sure we don't run the game in background
					//we can delete the player...
					delete player;
					player = nullptr;

				}
				return;
			}
		}

	}

	//check for life
	for (int i = 0; i < (int)lifes.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			lifes[i]->GetX(), lifes[i]->GetY(),
			player->GetRadius(), lifes[i]->GetRadius()
			))
		{

			cout << "Player gets an extra life\n";
			lives++;
			delete lifes[i];
			lifes[i] = nullptr;
			lifes.erase(lifes.begin() + i);


			return;
		}

	}

	//check for points
	for (int i = 0; i < (int)points.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			points[i]->GetX(), points[i]->GetY(),
			player->GetRadius(), points[i]->GetRadius()
			))
		{

			cout << "Player gets double points\n";
			
			delete points[i];
			points[i] = nullptr;
			points.erase(points.begin() + i);

			score = score * 2;
			return;
		}

	}
	bool isBreakOutOfLoop = false;
	//check for bullet and asteroid collision
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{

		for (int i = 0; i < (int)asteroids.size(); i++)
		{

			Bullet* bullet = player->GetBullets()[b];

			if (CircleCollisionTest(bullet->GetX(), bullet->GetY(),
				asteroids[i]->GetX(), asteroids[i]->GetY(),
				bullet->GetRadius(), asteroids[i]->GetRadius()
			))
			{

				cout << "Bullet collided with an asteroid!!\n";
				//may be, add to score here... 
				score += (asteroids[i]->GetRadius() / 100) * 5;
				asteroids[i]->lowRadius(asteroids[i]->getWidth());
				

				//cleanup/destroy the bullet
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);

				if (asteroids[i]->GetRadius() <= 10) {
					
					//destroy the asteroid
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);
					gone++;
				}
				if (gone==4)
				{
					Game::Instance()->GetFSM()->PushState(new GameStateTwo(lives,score)); 
				
				}
				isBreakOutOfLoop = true;

			}
			if (isBreakOutOfLoop)	break;
		}

		if (isBreakOutOfLoop)	break;
	}

	if (isBreakOutOfLoop)
	{
		player->GetBullets().shrink_to_fit();
		asteroids.shrink_to_fit();
	}

}
