#include "Gameloop.h"
#include<vector>
Gameloop* g = new Gameloop();


int main(int argc, char** argv) {
	double first;
	double last = 0;
	g->Intialize();
	
label:
	g->Mainmenu();
	while (g->getGamestate()) {
		g->Render();
		g->Event();
		g->Update();	
		first = SDL_GetTicks();
		if (first - last < 15)
		{
			SDL_Delay(18 - (int)(first - last));
		}
		last = first;
	}
	g->Replay();
	g->Reset();
	if(g->getGameisPlaying())goto label;
	g->Clear();
	return 0;
	
}
