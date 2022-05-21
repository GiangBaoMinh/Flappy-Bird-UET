#include "Replay.h"

Replay::Replay()
{
	isClicked = false;
}

void Replay::Initialize(SDL_Renderer* ren)
{
	replayBackground.CreateTexture("Image/replay.png", ren);
}

int Replay::EventHandling(SDL_Event& e)
{
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
	{
		return -1;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN && e.motion.x > 285 && e.motion.x < 510 && e.motion.y > 403 && e.motion.y < 470)
	{
		isClicked = true;
		return 1;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN && e.motion.x > 285 && e.motion.x < 510 && e.motion.y > 510 && e.motion.y < 575)
	{
		isClicked = true;
		return -1;
	}
	return 0;
}

void Replay::Render(SDL_Renderer* ren)
{
	replayBackground.Render(ren);
}

bool Replay::getClicked()
{
	return isClicked;
}

Replay::~Replay()
{
	isClicked = false;
}

void Replay::Reset() {
	isClicked = false;
}