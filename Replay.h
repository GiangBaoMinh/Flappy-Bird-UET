#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Background.h"

class Replay
{
private:
    bool isClicked = false;
    Background replayBackground;
public:
    Replay();
    ~Replay();
    void Initialize(SDL_Renderer* ren);
    int EventHandling(SDL_Event& e);
    void Render(SDL_Renderer* ren);
    bool getClicked();
    void Reset();;
};