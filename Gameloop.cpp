#include "Gameloop.h"


Gameloop::Gameloop()
{
	window = NULL;
	renderer = NULL;
	Gamestate = false;
	GameIsPlaying = false;
	p.setSrc(0, 0, 24, 32);
	p.setDest(25, HEIGHT / 2, 28, 38);

	ground1.setSrc(0, 0, 112, 336);
	ground1.setDest(0, 550, 112, 805);
	ground2.setSrc(0, 0, 112, 336);
	ground2.setDest(805, 550, 112, 805);

	Pipe_Above1.setSrc(0, 0, 320, 52);
	Pipe_Above1.setDest(400, -200, 400, 52);
	Pipe_Below1.setSrc(0, 0, 320, 52);
	Pipe_Below1.setDest(400, 350, 400, 52);
	Pipe_Above2.setSrc(0, 0, 320, 52);
	Pipe_Above2.setDest(700, -200, 400, 52);
	Pipe_Below2.setSrc(0, 0, 320, 52);
	Pipe_Below2.setDest(700, 350, 400, 52);
	Pipe_Above3.setSrc(0, 0, 320, 52);
	Pipe_Above3.setDest(1000, -200, 400, 52);
	Pipe_Below3.setSrc(0, 0, 320, 52);
	Pipe_Below3.setDest(1000, 350, 400, 52);

}

bool Gameloop::getGamestate()
{
	return Gamestate;
}
bool Gameloop::getGameisPlaying()
{
	return GameIsPlaying;
}

void Gameloop::Intialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("Flap game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window) {
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer suceeded!" << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			Gamestate = true;
			score.createFont("Font/04B_19__.TTF" ,38);

			p.CreateTexture("Image/yellowbird1.png", renderer);
			p.CreateTexture1("Image/yellowbird2.png", renderer);
			p.CreateTexture2("Image/yellowbird3.png", renderer);
			b.CreateTexture("Image/background.png", renderer);
			ground1.CreateTexture("Image/base.png", renderer);
			ground2.CreateTexture("Image/base.png", renderer);
			Pipe_Above1.CreateTexture("Image/pipe_Above.png", renderer);
			Pipe_Below1.CreateTexture("Image/pipe_Below.png", renderer);
			Pipe_Above2.CreateTexture("Image/pipe_Above.png", renderer);
			Pipe_Below2.CreateTexture("Image/pipe_Below.png", renderer);
			Pipe_Above3.CreateTexture("Image/Pipe_Above.png", renderer);
			Pipe_Below3.CreateTexture("Image/Pipe_Below.png", renderer);
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
				return;
			PunchSound = Mix_LoadWAV("Sound/sound_punch.wav");
			PointSound = Mix_LoadWAV("Sound/sound_ting.wav");
			
		}
		else {
			std::cout << "Renderer failed";
		}
		std::cout << "Window succeeded!";
		
	}
	else {
		std::cout << " Window failed";
	}
}

void Gameloop::Mainmenu()
{
	menu.Initialize(renderer);
	while (!menu.getClicked())
	{
		if (menu.EventHandling(event1) == -1)
		{
			GameIsPlaying = Gamestate = false;
			break;
		}
		else if (menu.EventHandling(event1) == 1)GameIsPlaying = Gamestate = true;
		SDL_RenderClear(renderer);
		menu.Render(renderer);
		SDL_RenderPresent(renderer);
	}
}
void Gameloop::Replay()
{	
	replay.Initialize(renderer);
	while (!replay.getClicked())
	{
		if (replay.EventHandling(event1) == -1)
		{
			Gamestate = GameIsPlaying = false;
			break;
		}
		else if (replay.EventHandling(event1) == 1) {
			Gamestate = GameIsPlaying = true;
		}
		SDL_RenderClear(renderer);
		replay.Render(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Gameloop::Event() {
	p.GetJumpTime();
	SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT) 
	{
			Gamestate = false;
	}
	if (event1.type == SDL_KEYDOWN)
	{
		if (event1.key.keysym.sym == SDLK_UP || event1.key.keysym.sym == SDLK_SPACE)
		{
			if (!p.JumpState())
			{
				p.Jump();
			}
			else
			{
				p.Gravity();
			}
		}
	}
	else
	{
		p.Gravity();
	}
}


void Gameloop::Update()
{

	std::string s;
	s = "Score: " + std::to_string(points);
	score.Text(s, WHITECOLOR, renderer);
	bool flag1 = false, flag2 = false;
	ground1.GroundUpdate1();
	ground2.GroundUpdate2();
	flag1 = Pipe_Above1.Pipe_Above1Update(variance1, points, PointSound);
	flag2 = Pipe_Below1.Pipe_Below1Update(variance1);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance1 = rand() % 201 - 100;
		Pipe_Above1.Pipe_Above1Update(variance1, points, PointSound);
		Pipe_Below1.Pipe_Below1Update(variance1);
	}
	flag1 = Pipe_Above2.Pipe_Above2Update(variance2, points, PointSound);
	flag2 = Pipe_Below2.Pipe_Below2Update(variance2);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance2 = rand() % 201 - 100;
		Pipe_Above2.Pipe_Above2Update(variance2, points, PointSound);
		Pipe_Below2.Pipe_Below2Update(variance2);
	}
	flag1 = Pipe_Above3.Pipe_Above3Update(variance3, points, PointSound);
	flag1 = Pipe_Below3.Pipe_Below3Update(variance3);
	if (flag1 && flag2)
	{
		srand(SDL_GetTicks());
		variance3 = rand() % 201 - 100;
		Pipe_Above3.Pipe_Above3Update(variance3, points, PointSound);
		Pipe_Below3.Pipe_Below3Update(variance3);
	}

	CollisionDetection();
}
	
void Gameloop::CollisionDetection()
{
	if (CollisionManager::CheckCollision(&p.getDest(), &Pipe_Above1.getDest()) || CollisionManager::CheckCollision(&p.getDest(), &Pipe_Below1.getDest()) ||
		CollisionManager::CheckCollision(&p.getDest(), &Pipe_Above2.getDest()) || CollisionManager::CheckCollision(&p.getDest(), &Pipe_Below2.getDest()) ||
		CollisionManager::CheckCollision(&p.getDest(), &Pipe_Above3.getDest()) || CollisionManager::CheckCollision(&p.getDest(), &Pipe_Below3.getDest()) ||
		CollisionManager::CheckCollision(&p.getDest(), &ground1.getDest()) || CollisionManager::CheckCollision(&p.getDest(), &ground2.getDest()) || p.getYpos() < 0)
	{
		Mix_PlayChannelTimed(-1, PunchSound, 0, 300);
		Gamestate = false;
		SDL_Delay(500);
	}
}

void Gameloop::Render()
{
	SDL_RenderClear(renderer);
	b.Render(renderer);
	Pipe_Above1.PipeRender(renderer);
	Pipe_Below1.PipeRender(renderer);
	Pipe_Above2.PipeRender(renderer);
	Pipe_Below2.PipeRender(renderer);
	Pipe_Above3.PipeRender(renderer);
	Pipe_Below3.PipeRender(renderer);
	p.Render(renderer);
	ground1.GroundRender(renderer);
	ground2.GroundRender(renderer);
	SDL_RenderPresent(renderer);
	score.Render(renderer,0,0);
}

void Gameloop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	score.closeFont();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
 }

void Gameloop::Reset()
{
	points = 0;
	variance1 = rand() % 201 - 100;
	variance2 = rand() % 201 - 100;
	variance3 = rand() % 201 - 100;
	p.Reset();
	Pipe_Above1.Reset();
	Pipe_Above2.Reset();
	Pipe_Above3.Reset();
	Pipe_Below1.Reset();
	Pipe_Below2.Reset();
	Pipe_Below3.Reset();
	menu.Reset();
	replay.Reset();
}