#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<cstdlib>
#include<string>
#include"Player.h"
#include"Background.h"
#include"Object.h"
#include"TextureManager.h"
#include"CollisionManager.h"
#include"Mainmenu.h"
#include"Replay.h"
#include"TextManager.h"

class Gameloop
{
private:
	Player p;
	Background b;
	Background ground1, ground2;
	Background Pipe_Above1;
	Background Pipe_Below1;
	Background Pipe_Above2;
	Background Pipe_Below2;
	Background Pipe_Above3;
	Background Pipe_Below3;
	MainMenu menu;
	TextManager score;
	TextManager recentscore;
	Replay replay;
	const int HEIGHT = 640;
	const int WIDTH = 800;
	int points = 0;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
	bool Gamestate;
	bool GameIsPlaying;
	const SDL_Color WHITECOLOR = { 255, 255, 255, 255 };
	const SDL_Color BLACKCOLOR = { 0, 0 ,0 , 0 };
	const SDL_Color REDCOLOR = { 255, 0, 0, 255 };
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event1;
	Mix_Chunk *PointSound,*PunchSound;
public:
	Gameloop(); 
	void Mainmenu();
	void Replay();
	bool getGamestate();
	bool getGameisPlaying();
	void Intialize();
	void Update();
	void Event();
	void CollisionDetection();
	void Render();
	void Clear();
	void Reset();
};