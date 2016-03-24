#pragma once
#include <vector>
#include "Text.h"
#include <SDL.h>

class TextManager
{
public:
	TextManager();
	~TextManager();

	void Render(SDL_Renderer *_renderer);

	Text * CreateNewText(Text::TextSetup &_textValues);
	void AddText(Text *_existingText);

private:
	std::vector<Text*> m_TextObjects;
};

