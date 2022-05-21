#include "TextManager.h"

void TextManager::createFont(const std::string path, const int size)
{
    font = TTF_OpenFont(path.c_str(), size);
    if (!font)
    {
        std::cout << TTF_GetError() << std::endl;
    }
}

void TextManager::Text(const std::string text, const SDL_Color color, SDL_Renderer* ren)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == NULL)
    {
        std::cout << TTF_GetError() << std::endl;
    }
    createTexture(textSurface, ren);
    SDL_FreeSurface(textSurface);
}

void TextManager::createTexture(SDL_Surface* sur, SDL_Renderer* ren)
{
    fontTexture = SDL_CreateTextureFromSurface(ren, sur);
}

void TextManager::Render(SDL_Renderer* ren, const int x, const int y)
{
    TextRect.x = x;
    TextRect.y = y;
    SDL_QueryTexture(fontTexture, NULL, NULL, &TextRect.w, &TextRect.h);
    SDL_RenderCopy(ren, fontTexture, NULL, &TextRect);
}

void TextManager::closeFont() {
    TTF_CloseFont(font);
}


